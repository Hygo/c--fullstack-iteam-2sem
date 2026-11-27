# 🧰 Instalação do compilador e do editor (passo a passo)

Para fazer as atividades você precisa de duas coisas:

- um **compilador C++**: o programa que traduz o seu arquivo `.cpp` em um executável;
- um **editor** para escrever o código (usamos o Visual Studio Code).

Instalar só o editor **não basta**. O trabalho só está pronto quando o comando `g++ --version` responde no seu terminal.

Todos os programas do curso usam **C++17** e são compilados com avisos ativados:

```bash
g++ -std=c++17 -Wall -Wextra programa.cpp -o programa
```

| Seu computador | Siga a seção | Tempo aproximado |
|----------------|--------------|------------------|
| Windows 10 (64 bits) ou Windows 11 | [1. Windows com MSYS2](#1-windows-com-msys2-ucrt64) | 20 a 30 minutos |
| Linux (Ubuntu, Debian, Fedora, Arch…) | [2. Linux](#2-linux) | 5 minutos |
| macOS | [3. macOS](#3-macos) | 10 minutos |

Depois, em qualquer sistema: [4. Editor VS Code](#4-editor-visual-studio-code) e [5. Teste final](#5-teste-final).

> **O que é o MSYS2?** É um conjunto de ferramentas para Windows que traz o `g++` (o mesmo compilador usado no Linux) e um gerenciador de pacotes chamado `pacman`. Ele existe **só para Windows**: no Linux o compilador vem direto do gerenciador da sua distribuição.

---

## 1. Windows com MSYS2 (UCRT64)

Reserve cerca de **2 GB livres** no disco e uma conexão de internet estável: o instalador é pequeno, mas os pacotes do compilador são baixados durante o processo.

### Passo 1 – Baixe o instalador

1. Abra <https://www.msys2.org> no navegador.
2. Baixe o instalador (um arquivo com nome parecido com `msys2-x86_64-AAAAMMDD.exe`).

### Passo 2 – Instale o MSYS2

1. Dê dois cliques no arquivo baixado. O instalador é em inglês.
2. Clique em **Next**.
3. Em *Installation Folder*, **mantenha `C:\msys64`** (não troque!). Os guias do curso e as configurações do VS Code assumem esse caminho. Clique em **Next**.
4. Nas telas seguintes, deixe as opções como estão e clique em **Next** (ou **Install**) até a cópia dos arquivos começar. Aguarde terminar.
5. Na última tela, deixe marcada a opção **Run MSYS2 now** e clique em **Finish**. Uma janela de terminal vai abrir.

> Não é preciso ser administrador para instalar. Se o computador for do laboratório e a instalação for bloqueada, avise o professor antes de tentar outro caminho.

### Passo 3 – Abra o terminal certo: **MSYS2 UCRT64**

O MSYS2 instala **vários terminais** no menu Iniciar (*MSYS2 MSYS*, *MSYS2 UCRT64*, *MSYS2 MINGW64*, *MSYS2 CLANG64*…). Para o curso usamos **somente o UCRT64**.

1. Feche a janela que abriu no passo anterior (ela pode não ser a UCRT64).
2. Abra o menu Iniciar, procure por **MSYS2 UCRT64** e abra.
3. Confira: o prompt deve mostrar a palavra `UCRT64`, na linha acima do cursor, parecido com isto:

   ```text
   aluno@PC UCRT64 ~
   $
   ```

4. Se tiver dúvida, digite `echo $MSYSTEM` e pressione Enter. A resposta tem de ser `UCRT64`.

> **Dica:** nos terminais do MSYS2, para colar use **Shift+Insert** ou o botão direito do mouse (o Ctrl+V comum pode não funcionar).

### Passo 4 – Atualize o MSYS2

No terminal **UCRT64**, digite:

```bash
pacman -Syu
```

- Quando aparecer `Proceed with installation? [Y/n]`, digite `Y` e pressione Enter.
- Se o terminal avisar que vai **fechar** para concluir a atualização, deixe fechar. Abra **MSYS2 UCRT64** de novo e repita `pacman -Syu`.
- Repita até aparecer `there is nothing to do` (nada a fazer). Normalmente são uma ou duas rodadas.

### Passo 5 – Instale o compilador e o depurador

Ainda no terminal **UCRT64**:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb
```

Responda `Y` (ou só Enter) quando perguntar `Proceed with installation?`. O download pode demorar alguns minutos.

- `gcc`: contém o `g++`, o compilador de C++.
- `gdb`: o depurador, que usaremos para investigar erros.

### Passo 6 – Teste dentro do terminal do MSYS2

```bash
g++ --version
gdb --version
```

Cada comando deve mostrar uma versão (a primeira linha começa com `g++.exe (...)` ou `g++ (...)`, e menciona `MSYS2 project`). Os números exatos mudam com o tempo; qualquer versão **10 ou mais nova** serve para o curso.

> A atividade **F1** pede a saída de `g++ --version`. Guarde essa tela.

Se aparecer `g++: command not found`, você provavelmente abriu o terminal errado (por exemplo, o *MSYS2 MSYS*). Feche e abra o **MSYS2 UCRT64**.

### Passo 7 – Coloque o compilador no `Path` do Windows

Este passo é **obrigatório para usar o VS Code**. Por enquanto o `g++` só funciona no terminal do MSYS2. Para usá-lo também no PowerShell, no `cmd` e dentro do VS Code, ensine o Windows onde ele está:

1. Aperte a tecla **Windows**, digite `variáveis de ambiente` e abra **Editar as variáveis de ambiente do sistema**.
2. Clique no botão **Variáveis de Ambiente…**.
3. Na parte de cima (**Variáveis de usuário para …**), selecione a linha **Path** e clique em **Editar…**.
4. Clique em **Novo** e digite exatamente:

   ```text
   C:\msys64\ucrt64\bin
   ```

5. Clique em **OK** nas três janelas, até todas fecharem.
6. **Feche todos os terminais e o VS Code** que estiverem abertos. A alteração só vale para programas abertos depois dela.

### Passo 8 – Teste no PowerShell

Abra o menu Iniciar, procure por **PowerShell** e execute:

```powershell
g++ --version
gdb --version
```

Se as versões aparecerem, o Windows está pronto. 🎉

Para saber **qual** `g++` está sendo usado:

```powershell
Get-Command g++
```

O caminho mostrado deve ser `C:\msys64\ucrt64\bin\g++.exe`. Se for outro, você tem outro compilador instalado antes dele no `Path`: veja a tabela de [problemas comuns](#6-problemas-comuns).

### Como usar o terminal do MSYS2 (opcional)

Se preferir compilar dentro do terminal UCRT64, lembre que as unidades do Windows viram pastas:

| No Windows | No terminal do MSYS2 |
|------------|----------------------|
| `C:\Users\aluno\Documentos` | `/c/Users/aluno/Documentos` |
| `D:\curso` | `/d/curso` |

Exemplo para entrar na pasta do curso: `cd /c/Users/aluno/Documentos/c--fullstack-iteam-2sem`. Use `pwd` para ver onde você está e `ls` para listar os arquivos.

### Manutenção (de vez em quando)

Para atualizar o compilador e as bibliotecas, abra o **MSYS2 UCRT64** e rode `pacman -Syu`. **Não** faça isso no meio das atividades de uma unidade, para não mudar a versão do compilador no meio do trabalho.

---

## 2. Linux

No Linux o MSYS2 **não é necessário**: o compilador vem do gerenciador de pacotes da distribuição. Abra um terminal e use o comando da sua distribuição:

| Distribuição | Comando |
|--------------|---------|
| Ubuntu, Debian, Linux Mint | `sudo apt update && sudo apt install build-essential gdb` |
| Fedora | `sudo dnf install gcc-c++ gdb` |
| Arch Linux, Manjaro | `sudo pacman -S base-devel gdb` |

O `sudo` pede a sua senha (ela não aparece enquanto você digita). Depois confirme:

```bash
g++ --version
gdb --version
```

Qualquer versão **10 ou mais nova** serve para o curso. Em distribuições muito antigas, se a versão for menor, atualize o sistema ou fale com o professor.

> **Windows com WSL?** Se você já usa o WSL (Linux dentro do Windows), pode seguir esta seção dentro dele. Mesmo assim, para o projeto final e para o laboratório o caminho recomendado é o MSYS2 da seção 1.

> **Detalhe do VS Code no Linux:** a tarefa de compilação do curso gera arquivos terminados em `.exe` (por exemplo, `f1_primeiro_programa.exe`). No Linux isso é só o nome: execute normalmente com `./f1_primeiro_programa.exe`.

---

## 3. macOS

Instale as ferramentas de linha de comando da Apple e confirme:

```bash
xcode-select --install
g++ --version
```

No macOS o `g++` é, na verdade, o compilador **Clang** da Apple. Para o curso ele funciona do mesmo jeito e os programas produzem a mesma saída.

---

## 4. Editor: Visual Studio Code

1. Baixe e instale o VS Code em <https://code.visualstudio.com>.
2. Abra o VS Code, clique no ícone de **Extensões** (quatro quadrados, na barra lateral) e instale **C/C++** (autor: Microsoft).
3. Em **Arquivo → Abrir Pasta…**, escolha a pasta da **sua cópia** do repositório do curso. (Ainda não tem a cópia? Veja [COMO-OBTER-AS-ATIVIDADES.md](../COMO-OBTER-AS-ATIVIDADES.md).)
4. Abra um arquivo `.cpp` e pressione **Ctrl+Shift+B**. A tarefa de compilação do curso (já configurada em `.vscode/tasks.json`) compila o **arquivo aberto** com `-std=c++17 -Wall -Wextra` e cria um `.exe` ao lado dele.
5. Abra o terminal do VS Code (**Ctrl+'** ou menu *Terminal → Novo Terminal*), entre na pasta do arquivo e execute:

   ```powershell
   cd unidade-01\resolucao
   .\f1_primeiro_programa.exe
   ```

   (No Linux e no macOS: `cd unidade-01/resolucao` e `./f1_primeiro_programa.exe`. O executável tem o mesmo nome do arquivo `.cpp`, trocando só a extensão.)

**Se o VS Code sublinhar `#include <iostream>` em vermelho:** o editor não encontrou o compilador. Pressione **Ctrl+Shift+P**, digite `C/C++: Edit Configurations (UI)` e preencha:

- *Compiler path*: `C:/msys64/ucrt64/bin/g++.exe` (no Windows) ou `/usr/bin/g++` (no Linux);
- *C++ standard*: `c++17`.

Outros editores (Code::Blocks, CLion, Visual Studio…) também servem, desde que você consiga compilar com as mesmas opções.

---

## 5. Teste final

Crie uma pasta de teste (fora do repositório do curso, por exemplo `Documentos\teste-cpp`) e, dentro dela, um arquivo `main.cpp` com este conteúdo:

```cpp
#include <iostream>

int main() {
    std::cout << "Ola, mundo!" << '\n';
    return 0;
}
```

Abra um terminal **nessa pasta** (PowerShell no Windows) e compile:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o programa
```

Execute:

```bash
./programa          # no PowerShell do Windows: .\programa.exe
```

Deve aparecer:

```text
Ola, mundo!
```

Se compilou **sem nenhum aviso** e a frase apareceu, o seu ambiente está pronto para a atividade F1. ✅

### Lista de conferência

- [ ] `g++ --version` mostra uma versão (10 ou mais nova)
- [ ] `gdb --version` mostra uma versão
- [ ] O `main.cpp` acima compila com `-std=c++17 -Wall -Wextra` e imprime `Ola, mundo!`
- [ ] (Windows) o teste funcionou também no **PowerShell** e no terminal do **VS Code**
- [ ] **Ctrl+Shift+B** compila o arquivo aberto no VS Code

---

## 6. Problemas comuns

| O que aparece | Causa provável | O que fazer |
|---------------|----------------|-------------|
| `g++` não é reconhecido… (no PowerShell ou no `cmd`) | o compilador não está no `Path`, ou o terminal foi aberto antes de você alterar o `Path` | refaça o [Passo 7](#passo-7--coloque-o-compilador-no-path-do-windows), **feche** todos os terminais e o VS Code e abra de novo |
| `g++: command not found` no terminal do MSYS2 | você abriu *MSYS2 MSYS* (ou outro) em vez do **UCRT64** | feche e abra o **MSYS2 UCRT64**; confira com `echo $MSYSTEM` |
| `Get-Command g++` mostra uma pasta diferente de `C:\msys64\ucrt64\bin` | existe outro compilador (por exemplo, um MinGW antigo) antes dele no `Path` | no Passo 7, mova `C:\msys64\ucrt64\bin` para o topo da lista (botão **Mover para cima**) ou remova o `Path` do outro compilador. Misturar compiladores é a causa mais comum de erros estranhos |
| `error: failed retrieving file` / `Could not resolve host` ao usar o `pacman` | internet instável, proxy ou firewall da rede | tente de novo; se persistir, teste em outra rede ou fale com o professor |
| `unable to lock database` | outro `pacman` ainda está aberto | feche todas as janelas do MSYS2, espere um minuto e tente de novo |
| O terminal do MSYS2 fecha sozinho durante o `pacman -Syu` | é esperado: a atualização do núcleo fecha o terminal | abra o **MSYS2 UCRT64** de novo e repita `pacman -Syu` |
| `No such file or directory` ao compilar | você está em outra pasta ou digitou o nome errado | use `pwd` (ou `Get-Location`) e `ls` para ver onde está; entre na pasta do arquivo com `cd` |
| A janela do programa fecha rápido ao dar duplo clique no `.exe` | o programa roda e termina antes de você ler | execute sempre **pelo terminal**, não pelo Explorador de Arquivos |
| `Permission denied` ao recompilar | o programa anterior ainda está em execução | feche o programa em execução e compile de novo |
| Acentos aparecem trocados na tela do Windows | codificação do terminal | nas atividades a saída é escrita **sem acentos** de propósito; mantenha como nos exemplos |
| O compilador antigo não aceita `-std=c++17` | versão muito antiga do `g++` | atualize (Windows: `pacman -Syu`; Linux: atualize o sistema) e confira `g++ --version` |

Continua com problema? Anote a **mensagem de erro completa** e a saída de `g++ --version` (e de `Get-Command g++`, no Windows) e fale com o professor. Com essas informações a resposta é bem mais rápida.
