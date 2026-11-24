// rotas_tarefas.hpp - Rotas HTTP do recurso "tarefas" (CRUD completo).
//
//   GET    /api/tarefas          lista
//   GET    /api/tarefas/:id      busca uma
//   POST   /api/tarefas          cria            (projeto_id inexistente -> 422)
//   PUT    /api/tarefas/:id      atualiza
//   DELETE /api/tarefas/:id      remove
#pragma once

#include <httplib.h>

#include "config.hpp"

void registrarRotasTarefas(httplib::Server& servidor, const Config& config);
