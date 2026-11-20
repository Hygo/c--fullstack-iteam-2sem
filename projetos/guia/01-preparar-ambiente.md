# Guia 1 — Preparar o ambiente (Windows)

**Quando fazer:** o quanto antes, de preferência antes do dia 6. **Todos os 4 integrantes** da equipe precisam de um ambiente funcionando.

Vamos instalar quatro coisas e testar tudo no final:

| O quê | Para quê |
|-------|----------|
| **MSYS2 (UCRT64)** | compilador `g++` e a biblioteca para falar com o MariaDB |
| **XAMPP** | servidor de banco de dados MariaDB (e o phpMyAdmin) |
| **Git** | versionamento (já instalado se você fez a seção 1 de [`COMO-OBTER-AS-ATIVIDADES.md`](../../COMO-OBTER-AS-ATIVIDADES.md)) |
| **VS Code** | editor (opcional, mas é o que usamos no curso) |

> Já tem um `g++` funcionando (por exemplo, do MinGW usado nas unidades)? Rode `g++ --version` e `g++ -dumpmachine`. Para este projeto, o caminho testado é o **MSYS2 UCRT64**. Misturar compiladores diferentes é a causa mais comum de erros estranhos de `undefined reference` e de DLLs faltando.

## 1. MSYS2 e o compilador

1. Baixe o instalador em <https://www.msys2.org> e instale em `C:\msys64` (o caminho padrão).
2. Abra o **MSYS2 UCRT64** pelo menu Iniciar (o ícone de fundo azul/ucrt; **não** o "MSYS2 MSYS"). A janela mostra `UCRT64` no prompt.
3. Atualize o sistema de pacotes (se o terminal pedir para fechar no meio, feche, abra de novo e repita):

   ```bash
   pacman -Syu
   ```

4. Instale o compilador, o depurador e a biblioteca cliente do MariaDB:

   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb mingw-w64-ucrt-x86_64-libmariadbclient
   ```

5. Confira:

   ```bash
   g++ --version
   mariadb_config --version
   ls /ucrt64/include/mariadb/mysql.h
   ```

   Os três comandos devem funcionar (o último deve mostrar o caminho do arquivo `mysql.h`).

### Deixar o `g++` disponível fora do terminal do MSYS2 (recomendado)

Para compilar pelo terminal do VS Code (PowerShell) e pelo `cmd`, acrescente `C:\msys64\ucrt64\bin` ao `PATH` do Windows:

1. Menu Iniciar → procure **"Editar as variáveis de ambiente do sistema"** → *Variáveis de Ambiente…*
2. Em *Variáveis do usuário*, selecione `Path` → *Editar* → *Novo* → `C:\msys64\ucrt64\bin` → OK em tudo.
3. **Feche e abra** o terminal (e o VS Code) e teste `g++ --version`.

Isso também coloca a `libmariadb.dll` no caminho, e é por isso que o `servidor.exe` consegue abrir fora do MSYS2.

## 2. XAMPP (MariaDB)

1. Baixe em <https://www.apachefriends.org> e instale. Basta marcar **MySQL** (que no XAMPP é o MariaDB) e **phpMyAdmin** (o phpMyAdmin precisa do **Apache**, então deixe o Apache marcado também).
2. Abra o **XAMPP Control Panel** e clique em **Start** em *MySQL* (e em *Apache*, se for usar o phpMyAdmin).
3. Confira: abra <http://localhost/phpmyadmin>. Deve aparecer a lista de bancos de dados.

> **Por que instalamos a biblioteca do MariaDB no MSYS2 se o XAMPP já tem o MariaDB?** O XAMPP traz o **servidor**. Para o nosso programa em C++ *conversar* com o servidor, precisamos dos arquivos de desenvolvimento do **cliente** (`mysql.h` e `libmariadb`), que o XAMPP não garante ter. A biblioteca do MSYS2 se conecta ao servidor do XAMPP normalmente, pela porta 3306.

**A porta 3306 está ocupada?** Se o MySQL do XAMPP não iniciar, outro MySQL/MariaDB pode estar rodando. Pare o outro serviço ou mude a porta do XAMPP (*Config → my.ini*, `port=3307`) e informe ao projeto com a variável de ambiente `DB_PORTA=3307`.

## 3. Teste final: rodar o starter kit

Dentro da cópia da equipe (já clonada):

1. Importe o banco: abra <http://localhost/phpmyadmin> → aba **Importar** → escolha `projetos/starter-kit/schema.sql` → **Importar**. Deve aparecer o banco `projeto_iteam` com a tabela `recados`.
2. Compile (escolha **um** dos dois jeitos):

   | Onde | Comando |
   |------|---------|
   | Terminal do VS Code / `cmd` / PowerShell, dentro de `projetos\starter-kit` | `build.bat` |
   | Terminal **MSYS2 UCRT64**, dentro de `projetos/starter-kit` | `./build.sh` |

   A primeira compilação demora (de 30 segundos a alguns minutos, dependendo do computador). É normal.
3. Execute **dentro da pasta `starter-kit`**:

   ```bash
   build/servidor.exe
   ```

4. Abra <http://localhost:8080>. Se aparecer a tela de **Recados** com o registro "Bem-vindo", **o ambiente está pronto** ✅.
5. Teste também <http://localhost:8080/api/saude/banco>: deve mostrar `{"banco":"ok"}`.

Quem terminar primeiro ajuda os colegas da equipe. Só siga para o guia 02 quando **os quatro** estiverem com a tela funcionando.

## 4. Git: identifique-se

Cada pessoa configura o próprio nome e e-mail **uma vez**. É assim que o professor enxerga a sua contribuição:

```bash
git config --global user.name "Seu Nome"
git config --global user.email "o-mesmo-email-da-sua-conta-do-github@exemplo.com"
git config --global user.name    # confira
```

## 5. Plano B: se a biblioteca do MSYS2 não funcionar

Se o `pacman` não conseguir instalar o `libmariadbclient`, ou a compilação reclamar de `mysql.h`/`-lmariadb`, use o **MariaDB Connector/C** oficial:

1. Baixe o instalador **MSI de 64 bits** do *MariaDB Connector/C* em <https://mariadb.com/downloads/connectors/connectors-data-access/c-connector> (o `g++` do UCRT64 é 64 bits; a versão de 32 bits **não** serve).
2. Instale (por exemplo, em `C:\Program Files\MariaDB\MariaDB Connector C 64-bit`).
3. Antes de compilar, informe a pasta:

   ```bat
   set "MARIADB_DIR=C:\Program Files\MariaDB\MariaDB Connector C 64-bit"
   build.bat
   ```

4. Para **executar**, a `libmariadb.dll` precisa ser encontrada: copie-a da pasta `lib\mariadb` do Connector para `build\` (ao lado do `servidor.exe`).

Se ainda assim não funcionar, **chame o professor** com a mensagem de erro completa (print da tela inteira).

## 6. Problemas comuns

| Sintoma | O que fazer |
|---------|-------------|
| `g++` não é reconhecido | O `PATH` não tem `C:\msys64\ucrt64\bin`, ou o terminal foi aberto antes de alterá-lo. Feche e abra de novo. |
| `mysql.h: No such file or directory` | A biblioteca não foi instalada (passo 1.4) ou o `MARIADB_DIR` está errado (Plano B). |
| `cannot find -lmariadb` | Mesma causa. No MSYS2, `pacman -S mingw-w64-ucrt-x86_64-libmariadbclient`. |
| `undefined reference to 'WSAStartup'` (ou outros `__imp_...`) | Faltou `-lws2_32` na linha de comando. O `build.bat` e o `build.sh` já incluem; se compilar à mão, acrescente. |
| `servidor.exe` fecha logo ou diz que falta `libmariadb.dll` | A DLL não está no `PATH`. Rode pelo terminal do MSYS2 UCRT64, ou copie `libmariadb.dll` para `build\`. |
| `Can't connect to server on '127.0.0.1'` | O MySQL do XAMPP não está ligado (ou está em outra porta: `DB_PORTA`). |
| `Access denied for user 'root'` | O XAMPP padrão não tem senha. Se alguém definiu uma, use `DB_SENHA`. |
| `Unknown database 'projeto_iteam'` | Falta importar o `schema.sql`. |
| Antivírus ou firewall bloqueia o `servidor.exe` | Permita o acesso em rede privada. O servidor só escuta em `127.0.0.1` (o próprio computador). |
