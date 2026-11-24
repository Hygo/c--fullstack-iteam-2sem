#include "tarefa_repositorio.hpp"

#include "parametros.hpp"

using nlohmann::json;

namespace {

// JOIN: cada tarefa traz o nome do projeto. Todas as tarefas têm projeto (FK NOT NULL), então JOIN simples basta.
const char* const kSelect =
    "SELECT t.id, t.projeto_id, p.nome AS projeto_nome, t.titulo, t.descricao, t.status, t.prioridade, "
    "t.prazo, t.horas_estimadas, t.concluida_em, t.criado_em "
    "FROM tarefas t JOIN projetos p ON p.id = t.projeto_id ";

}  // namespace

json TarefaRepositorio::listar() {
    return banco_.consultar(std::string(kSelect) + "ORDER BY t.id DESC");
}

json TarefaRepositorio::buscar(long long id) {
    json linhas = banco_.consultar(std::string(kSelect) + "WHERE t.id = ?", {std::to_string(id)});
    return linhas.empty() ? json(nullptr) : linhas.front();
}

json TarefaRepositorio::criar(const json& dados) {
    const std::string status = parametros::opcional(dados, "status", "pendente");
    // NULLIF(?, ''): descrição, prazo e horas vazios viram NULL de verdade.
    // concluida_em: se a tarefa já nasce "feito", registramos o momento da conclusão.
    banco_.executar(
        "INSERT INTO tarefas (projeto_id, titulo, descricao, status, prioridade, prazo, horas_estimadas, concluida_em) "
        "VALUES (?, ?, NULLIF(?, ''), ?, ?, NULLIF(?, ''), NULLIF(?, ''), CASE WHEN ? = 'feito' THEN NOW() ELSE NULL END)",
        {parametros::comoTexto(dados.at("projeto_id")), parametros::comoTexto(dados.at("titulo")),
         parametros::opcional(dados, "descricao"), status, parametros::opcional(dados, "prioridade", "3"),
         parametros::opcional(dados, "prazo"), parametros::opcional(dados, "horas_estimadas"), status});
    return buscar(static_cast<long long>(banco_.ultimoId()));
}

json TarefaRepositorio::atualizar(long long id, const json& dados) {
    // Conferimos se existe ANTES: um UPDATE que não muda nenhum valor devolve 0 linhas afetadas,
    // e não poderíamos distinguir "id inexistente" de "nada mudou".
    if (buscar(id).is_null()) {
        return json(nullptr);
    }
    const std::string status = parametros::opcional(dados, "status", "pendente");
    // concluida_em: ao virar "feito" guarda o momento (sem sobrescrever se já estava feito); ao sair de "feito", limpa.
    banco_.executar(
        "UPDATE tarefas SET projeto_id = ?, titulo = ?, descricao = NULLIF(?, ''), status = ?, prioridade = ?, "
        "prazo = NULLIF(?, ''), horas_estimadas = NULLIF(?, ''), "
        "concluida_em = CASE WHEN ? = 'feito' THEN COALESCE(concluida_em, NOW()) ELSE NULL END "
        "WHERE id = ?",
        {parametros::comoTexto(dados.at("projeto_id")), parametros::comoTexto(dados.at("titulo")),
         parametros::opcional(dados, "descricao"), status, parametros::opcional(dados, "prioridade", "3"),
         parametros::opcional(dados, "prazo"), parametros::opcional(dados, "horas_estimadas"), status,
         std::to_string(id)});
    return buscar(id);
}

bool TarefaRepositorio::remover(long long id) {
    return banco_.executar("DELETE FROM tarefas WHERE id = ?", {std::to_string(id)}) > 0;
}
