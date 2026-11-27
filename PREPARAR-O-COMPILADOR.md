# Preparar o compilador e o editor

Para fazer as atividades você precisa de um **compilador C++** (o programa que traduz o seu `.cpp` em um executável) e de um **editor** para escrever o código. Instalar só o editor não basta: confirme sempre que o compilador respondeu à versão (`g++ --version`).

Todos os programas do curso usam **C++17** e são compilados com avisos ativados:

```bash
g++ -std=c++17 -Wall -Wextra programa.cpp -o programa
```

## Windows: MSYS2 (UCRT64)

Recomendamos o **MSYS2 UCRT64**. Ele é o mesmo ambiente que será usado no projeto final, então você instala uma vez só.

1. Baixe o instalador em <https://www.msys2.org> e instale em `C:\msys64` (caminho padrão).
2. Abra o **MSYS2 UCRT64** pelo menu Iniciar (ícone de fundo azul; **não** o "MSYS2 MSYS"). O prompt mostra `UCRT64`.
3. Atualize os pacotes (se o terminal pedir para fechar no meio, feche, abra de novo e repita):

   ```bash
   pacman -Syu
   ```

4. Instale o compilador e o depurador:

   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb
   ```

5. Confira:

   ```bash
   g++ --version
   ```

### Usar o `g++` fora do terminal do MSYS2 (recomendado)

Para compilar pelo terminal do VS Code (PowerShell) e pelo `cmd`, acrescente `C:\msys64\ucrt64\bin` ao `PATH` do Windows:

1. Menu Iniciar → **"Editar as variáveis de ambiente do sistema"** → *Variáveis de Ambiente…*
2. Em *Variáveis do usuário*, selecione `Path` → *Editar* → *Novo* → `C:\msys64\ucrt64\bin` → OK em tudo.
3. **Feche e abra** o terminal (e o VS Code) e teste `g++ --version`.

> Já tem outro `g++` (por exemplo, de um MinGW antigo)? Rode `g++ --version` e `g++ -dumpmachine`. Misturar compiladores diferentes é a causa mais comum de erros estranhos; se der problema, deixe só o do MSYS2 no `PATH`.

## Linux

Instale o pacote de desenvolvimento da sua distribuição e confira a versão:

```bash
# Ubuntu / Debian
sudo apt update && sudo apt install build-essential gdb

# Fedora
sudo dnf install gcc-c++ gdb

g++ --version
```

## macOS

Instale as ferramentas de linha de comando da Apple e confira:

```bash
xcode-select --install
g++ --version
```

No macOS o `g++` é o compilador Clang da Apple; para o curso isso funciona, e o resultado dos programas é o mesmo.

## Editor: Visual Studio Code

1. Instale o [VS Code](https://code.visualstudio.com) e a extensão **C/C++** (da Microsoft).
2. Use *Arquivo → Abrir Pasta…* na pasta da sua cópia do repositório.
3. Com um arquivo `.cpp` aberto, **Ctrl+Shift+B** compila com `-std=c++17 -Wall -Wextra` (tarefa pronta em `.vscode/tasks.json`) e gera um `.exe` ao lado do arquivo.
4. Execute pelo terminal do VS Code: `./nome.exe` (no PowerShell: `.\nome.exe`).

Outras opções (Code::Blocks, CLion, Visual Studio) também servem, desde que você consiga compilar com as mesmas opções.

## Teste final

Crie um arquivo `main.cpp`:

```cpp
#include <iostream>

int main() {
    std::cout << "Ola, mundo!" << '\n';
    return 0;
}
```

Compile e execute:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o programa
./programa
```

Deve aparecer `Ola, mundo!` (no Windows, `programa.exe`). Se aparecer, o ambiente está pronto.

## Problemas comuns

| O que aparece | Causa provável | O que fazer |
|---------------|----------------|-------------|
| `g++` não é reconhecido como comando | o compilador não está no `PATH` | siga "Usar o `g++` fora do terminal do MSYS2" e **reabra** o terminal |
| `No such file or directory` ao compilar | você está em outra pasta | use `cd` até a pasta do arquivo, ou informe o caminho completo |
| O terminal fecha rápido ao executar o `.exe` | foi aberto com duplo clique | execute pelo terminal, não pelo Explorador de Arquivos |
| Acentos aparecem trocados na tela | codificação do terminal do Windows | nas atividades a saída é escrita **sem acentos** de propósito; mantenha como está nos exemplos |
| `Permission denied` ao recompilar | o programa anterior ainda está rodando | feche o programa em execução e compile de novo |
