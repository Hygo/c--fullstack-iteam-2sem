# Starter kit — API em C++ + MariaDB + front-end

Um CRUD **completo e funcionando** (o recurso de exemplo se chama *recados*) para a sua equipe usar como ponto de partida. O trabalho de vocês é **trocar o exemplo pelo tema do projeto** e deixar tudo bem feito, não construir a infraestrutura do zero.

```
Navegador (public/index.html + app.js)
        │  fetch() com JSON
        ▼
Servidor C++ (cpp-httplib)  ──►  rotas_*.cpp  ──►  *_repositorio.cpp  ──►  MariaDB (XAMPP)
```

## Estrutura

```
starter-kit/
├── build.sh / build.bat     compilam o servidor (build.sh só recompila o que mudou)
├── schema.sql               cria o banco "projeto_iteam" e as tabelas
├── libs/                    bibliotecas de terceiros (não precisa instalar nada além do MariaDB):
│   ├── httplib.h            cpp-httplib (servidor HTTP)
│   └── nlohmann/json.hpp    nlohmann/json (JSON)
├── src/
│   ├── main.cpp             liga tudo: rotas, arquivos estáticos, tratamento de erros, porta
│   ├── config.hpp           host/usuário/senha do banco e porta do servidor
│   ├── banco.hpp/.cpp       conexão com o MariaDB (consultar / executar, com parâmetros "?")
│   ├── http_util.hpp        enviarJson, enviarErro, lerCorpoObjeto, lerId, comBanco
│   ├── recado_repositorio.* TODO o SQL do recurso "recados"
│   └── rotas_recados.*      rotas HTTP + validação do recurso "recados"
└── public/                  front-end (o servidor entrega estes arquivos ao navegador)
    ├── index.html
    ├── estilo.css
    ├── config.js            ← a configuração da tela (título, recurso da API, campos): é o que se edita
    └── app.js               CRUD genérico: monta tabela, formulário e busca a partir do config.js
```

## Rodando pela primeira vez

Pré-requisitos (compilador, XAMPP e a biblioteca do MariaDB): [`../guia/01-preparar-ambiente.md`](../guia/01-preparar-ambiente.md).

1. **Ligue o MySQL no painel do XAMPP** (botão *Start* do MySQL).
2. **Importe o `schema.sql`** — pelo phpMyAdmin (`http://localhost/phpmyadmin` → *Importar*) ou, no `cmd` (não no PowerShell), `C:\xampp\mysql\bin\mysql.exe -u root < schema.sql`.
3. **Compile** (a primeira vez demora, pois a `httplib.h` é grande):
   - terminal do MSYS2 UCRT64: `./build.sh`
   - `cmd` ou PowerShell: `build.bat`
4. **Execute, dentro da pasta do starter kit** (o servidor procura `./public` a partir dela):
   - `./build/servidor.exe` (ou `./build.sh rodar`)
5. Abra **http://localhost:8080** no navegador. Você deve ver a tela de *Recados* com um registro de boas-vindas.

Se algo falhar, veja a seção *Problemas comuns*, no fim deste arquivo.

## Testando a API sem o front-end

Com o servidor rodando, em outro terminal:

```bash
curl http://localhost:8080/api/saude                    # {"status":"ok"}
curl http://localhost:8080/api/saude/banco              # {"banco":"ok"}  (testa a conexão com o MariaDB)
curl http://localhost:8080/api/recados                  # lista
curl "http://localhost:8080/api/recados?busca=bem"      # busca
curl -X POST http://localhost:8080/api/recados -d '{"titulo":"Teste","prioridade":2}'
curl -X PUT  http://localhost:8080/api/recados/2 -d '{"titulo":"Novo titulo"}'
curl -X DELETE http://localhost:8080/api/recados/2
```

> Estes exemplos usam as aspas do bash: rode-os no **terminal do MSYS2**. No `cmd` e no PowerShell as aspas funcionam de outro jeito (e, no PowerShell, `curl` é um apelido de outro comando; use `curl.exe`). Outra opção é testar com a extensão *Thunder Client* do VS Code.

## Padrão das respostas

| Situação | Status | Corpo |
|----------|:------:|-------|
| Lista / busca / atualização OK | 200 | JSON (array ou objeto) |
| Criado | 201 | o registro criado |
| Removido | 204 | vazio |
| JSON inválido ou id inválido | 400 | `{"erro": "..."}` |
| Registro não encontrado / rota inexistente | 404 | `{"erro": "..."}` |
| Valor único repetido ou registro relacionado | 409 | `{"erro": "..."}` |
| Dados que não passam na validação (ou numa regra `CHECK` do banco) | 422 | `{"erro": "Dados invalidos", "detalhes": ["...", "..."]}` |
| Falha no banco / erro interno | 500 | `{"erro": "..."}` (os detalhes ficam só no console do servidor) |

## Como trocar o exemplo pelo seu tema

Siga sempre esta ordem; cada passo pode ser testado antes do próximo.

1. **Tabela** — em `schema.sql`, crie a tabela do seu tema (veja o tema em [`../temas/`](../temas/)) e reimporte o arquivo.
2. **Repositório** — copie `recado_repositorio.hpp/.cpp` para `livro_repositorio.*` (ou `pet_`, `produto_`) e ajuste o nome da classe, as colunas e os SQLs. **Todo SQL fica aqui.**
3. **Rotas** — copie `rotas_recados.hpp/.cpp` para `rotas_livros.*` e ajuste os caminhos (`/api/livros`), a validação e as mensagens.
4. **Registro** — em `main.cpp`, inclua o cabeçalho novo e chame `registrarRotasLivros(servidor, config);`.
5. **Compilação** — o `build.sh` já enxerga os novos `.cpp` de `src/`. No `build.bat`, acrescente-os na lista `FONTES`.
6. **Front-end** — em `public/config.js`, troque o título, o recurso e os campos. Para uma segunda tela (a entidade de apoio), copie `index.html` e o `config.js` (veja o guia 05).
7. **Teste com `curl` e depois no navegador**, e só então faça o *commit*.

Os guias [`03-json-e-validacao.md`](../guia/03-json-e-validacao.md), [`04-banco-mariadb.md`](../guia/04-banco-mariadb.md) e [`05-front-end.md`](../guia/05-front-end.md) explicam cada parte.

## Configuração (variáveis de ambiente)

Os padrões servem para o XAMPP. Para mudar sem editar o código, defina antes de executar (no `cmd`: `set NOME=valor`; no MSYS2/bash: `export NOME=valor`):

| Variável | Padrão | Para que serve |
|----------|--------|----------------|
| `DB_HOST` | `127.0.0.1` | endereço do MariaDB |
| `DB_PORTA` | `3306` | porta do MariaDB |
| `DB_USUARIO` | `root` | usuário |
| `DB_SENHA` | *(vazia)* | senha |
| `DB_NOME` | `projeto_iteam` | nome do banco |
| `PORTA` | `8080` | porta do servidor (também aceita `servidor.exe 8081`) |

## O que pode e o que não deve mudar

- **Podem e devem mudar:** `schema.sql`, `src/recado_*`, `src/rotas_*`, `src/main.cpp` (para registrar rotas), `public/*`.
- **Mudem com cuidado:** `banco.*` e `http_util.hpp` — são usados por todas as rotas. Se alterar, avise a equipe.
- **Não editem:** `libs/` (código de terceiros).
- **Regra de ouro do SQL:** valores **sempre** em parâmetros `?`, nunca concatenados no texto do SQL (SQL injection).

## Problemas comuns

| Sintoma | Causa provável e o que fazer |
|---------|------------------------------|
| `AVISO: Nao foi possivel conectar ao banco` | O MySQL do XAMPP não está ligado, a porta/usuário/senha são outros (variáveis `DB_*`) ou o `schema.sql` não foi importado. |
| `Unknown database 'projeto_iteam'` | Importe o `schema.sql`. |
| `mysql.h: No such file or directory` / `cannot find -lmariadb` | Falta a biblioteca cliente do MariaDB. Veja o guia 01 (instalação via `pacman` ou o MariaDB Connector/C) e, se necessário, defina `MARIADB_DIR`. |
| `ERRO: nao foi possivel usar a porta 8080` | Outro programa já usa a porta (talvez uma execução anterior do servidor). Feche-o ou rode `servidor.exe 8081`. |
| `AVISO: pasta ./public nao encontrada` | Você executou o servidor de outra pasta. Entre na pasta do starter kit antes de executar. |
| Janela fecha ao abrir o `.exe` e/ou erro sobre `libmariadb.dll` | A DLL do MariaDB não está no `PATH`. Rode pelo terminal do MSYS2 ou copie a `libmariadb.dll` para a pasta `build/`. |
| Alterei o código e nada mudou | Compile de novo (`./build.sh`) e **reinicie** o servidor. Para mudanças só no `public/`, basta recarregar a página (Ctrl+F5). |
| Acentos estranhos no navegador | Salve os arquivos do projeto em **UTF-8**. |

## Créditos das bibliotecas

[cpp-httplib](https://github.com/yhirose/cpp-httplib) (licença MIT) e [nlohmann/json](https://github.com/nlohmann/json) (licença MIT). Os textos das licenças estão em `libs/`.
