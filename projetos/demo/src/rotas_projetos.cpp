#include "rotas_projetos.hpp"

#include <string>

#include <nlohmann/json.hpp>

#include "http_util.hpp"
#include "projeto_repositorio.hpp"

using nlohmann::json;

namespace {

// Confere os campos recebidos. Devolve uma lista de mensagens; vazia = tudo certo.
json validarProjeto(const json& dados) {
    json erros = json::array();

    if (!dados.contains("nome") || !dados["nome"].is_string() || dados["nome"].get<std::string>().empty()) {
        erros.push_back("nome e obrigatorio");
    } else if (dados["nome"].get<std::string>().size() > 80) {
        erros.push_back("nome deve ter no maximo 80 caracteres");
    }

    if (dados.contains("descricao") && !dados["descricao"].is_null()) {
        if (!dados["descricao"].is_string()) {
            erros.push_back("descricao deve ser texto");
        } else if (dados["descricao"].get<std::string>().size() > 255) {
            erros.push_back("descricao deve ter no maximo 255 caracteres");
        }
    }
    return erros;
}

}  // namespace

void registrarRotasProjetos(httplib::Server& servidor, const Config& config) {
    // LISTAR
    servidor.Get("/api/projetos", [&config](const httplib::Request&, httplib::Response& res) {
        util::comBanco(config, res, [&](Conexao& banco) {
            ProjetoRepositorio repositorio(banco);
            util::enviarJson(res, repositorio.listar());
        });
    });

    // CRIAR
    servidor.Post("/api/projetos", [&config](const httplib::Request& req, httplib::Response& res) {
        json dados;
        if (!util::lerCorpoObjeto(req, res, dados)) {
            return;
        }
        json erros = validarProjeto(dados);
        if (!erros.empty()) {
            util::enviarErro(res, 422, "Dados invalidos", erros);
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            ProjetoRepositorio repositorio(banco);
            util::enviarJson(res, repositorio.criar(dados), 201);  // nome repetido: comBanco responde 409
        });
    });

    // REMOVER
    servidor.Delete("/api/projetos/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            ProjetoRepositorio repositorio(banco);
            if (!repositorio.remover(id)) {
                util::enviarErro(res, 404, "Projeto nao encontrado");
                return;
            }
            res.status = 204;  // sem conteudo (se o projeto tiver tarefas, comBanco responde 409)
        });
    });
}
