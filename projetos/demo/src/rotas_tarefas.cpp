#include "rotas_tarefas.hpp"

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "http_util.hpp"
#include "projeto_repositorio.hpp"
#include "tarefa_repositorio.hpp"
#include "validacao.hpp"

using nlohmann::json;

namespace {

const std::vector<std::string> kStatusPermitidos = {"pendente", "andamento", "feito"};

// Confere os campos recebidos. Devolve uma lista de mensagens; vazia = tudo certo.
json validarTarefa(const json& dados) {
    json erros = json::array();
    validacao::textoObrigatorio(dados, "titulo", 100, erros);
    validacao::textoOpcional(dados, "descricao", 65535, erros);
    validacao::inteiroEmFaixa(dados, "projeto_id", 1, 4294967295LL, true, erros);
    validacao::valorDaLista(dados, "status", kStatusPermitidos, erros);
    validacao::inteiroEmFaixa(dados, "prioridade", 1, 5, false, erros);
    validacao::dataOpcional(dados, "prazo", erros);
    validacao::decimalEmFaixa(dados, "horas_estimadas", 0, 9999.9, erros);
    return erros;
}

// Chave estrangeira: confere ANTES de gravar se o projeto existe, para responder 422 com uma mensagem clara
// (sem isso, o banco recusaria com o erro 1452 e a API devolveria um 409 genérico).
bool projetoExiste(Conexao& banco, const json& dados) {
    return !ProjetoRepositorio(banco).buscar(dados.at("projeto_id").get<long long>()).is_null();
}

}  // namespace

void registrarRotasTarefas(httplib::Server& servidor, const Config& config) {
    // LISTAR
    servidor.Get("/api/tarefas", [&config](const httplib::Request&, httplib::Response& res) {
        util::comBanco(config, res, [&](Conexao& banco) {
            TarefaRepositorio repositorio(banco);
            util::enviarJson(res, repositorio.listar());
        });
    });

    // BUSCAR UMA
    servidor.Get("/api/tarefas/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            TarefaRepositorio repositorio(banco);
            json tarefa = repositorio.buscar(id);
            if (tarefa.is_null()) {
                util::enviarErro(res, 404, "Tarefa nao encontrada");
                return;
            }
            util::enviarJson(res, tarefa);
        });
    });

    // CRIAR
    servidor.Post("/api/tarefas", [&config](const httplib::Request& req, httplib::Response& res) {
        json dados;
        if (!util::lerCorpoObjeto(req, res, dados)) {
            return;
        }
        json erros = validarTarefa(dados);
        if (!erros.empty()) {
            util::enviarErro(res, 422, "Dados invalidos", erros);
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            if (!projetoExiste(banco, dados)) {
                util::enviarErro(res, 422, "Dados invalidos", json::array({"projeto_id nao existe"}));
                return;
            }
            TarefaRepositorio repositorio(banco);
            util::enviarJson(res, repositorio.criar(dados), 201);
        });
    });

    // ATUALIZAR (substitui todos os campos)
    servidor.Put("/api/tarefas/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        json dados;
        if (!util::lerCorpoObjeto(req, res, dados)) {
            return;
        }
        json erros = validarTarefa(dados);
        if (!erros.empty()) {
            util::enviarErro(res, 422, "Dados invalidos", erros);
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            if (!projetoExiste(banco, dados)) {
                util::enviarErro(res, 422, "Dados invalidos", json::array({"projeto_id nao existe"}));
                return;
            }
            TarefaRepositorio repositorio(banco);
            json atualizada = repositorio.atualizar(id, dados);
            if (atualizada.is_null()) {
                util::enviarErro(res, 404, "Tarefa nao encontrada");
                return;
            }
            util::enviarJson(res, atualizada);
        });
    });

    // REMOVER
    servidor.Delete("/api/tarefas/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            TarefaRepositorio repositorio(banco);
            if (!repositorio.remover(id)) {
                util::enviarErro(res, 404, "Tarefa nao encontrada");
                return;
            }
            res.status = 204;  // sem conteudo
        });
    });
}
