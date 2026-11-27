# 📚 Aulas

Slides das aulas em PDF. Esta pasta cresce aos poucos: cada aula só aparece aqui depois de ministrada.

| Aula | Tema | Seções | Slides | Atividades para fixar |
|------|------|--------|--------|-----------------------|
| 1 | Introdução ao C++ I | 1.1 a 1.3 | [Aula_01_Modulo08_Cpp.pdf](aula-01/Aula_01_Modulo08_Cpp.pdf) | [`unidade-01/`](../unidade-01/exercicios.md): nível fácil (F1 a F5) |

## O que a Aula 1 cobre

- **1.1 História e evolução do C++:** da linguagem *C with Classes* (1979) ao C++ (1983) e ao padrão C++17, que usamos no curso.
- **1.2 Ambiente de desenvolvimento:** editor, compilador e depurador; como conferir a instalação (`g++ --version`) e compilar com `g++ -std=c++17 -Wall -Wextra main.cpp -o programa`.
- **1.3 Variáveis e identificadores:** declarar e inicializar (`int x{0};`), escolher o tipo adequado e usar os operadores (`=` atribui, `==` compara; `/` entre inteiros é divisão inteira).
- **Exemplos 1 a 3:** primeiro programa completo, declaração e inicialização, expressões aritméticas.
- **Atividades 1 a 3 (feitas em sala):** instalação e compilação, variáveis e tipos, operadores.

## Depois da aula

As atividades de fixação estão em [`unidade-01/exercicios.md`](../unidade-01/exercicios.md). Com o conteúdo desta aula você já consegue resolver o **nível fácil**:

| Atividade | Combina com |
|-----------|-------------|
| 🟢 F1 – Primeiro programa, compilado com avisos | Atividade 1 da aula |
| 🟢 F2 – Variáveis e tipos: ficha de matrícula | Atividade 2 da aula |
| 🟢 F3 – Operadores aritméticos e divisão por zero | Atividade 3 da aula |
| 🟢 F4 – Conversor de temperatura | Seções 1.3 (tipos) e operadores; atenção à divisão inteira |
| 🟢 F5 – Troca de variáveis: achando o defeito | Seção 1.3 (atribuição); o enunciado apresenta o `std::swap` |

Os níveis intermediário e difícil usam assuntos que ainda vão ser vistos (por exemplo `std::getline` e a formatação da saída), então deixe-os para depois das próximas aulas.

## Como trazer as aulas novas para a sua cópia

Quando o professor avisar que há aula nova, na sua cópia do repositório:

```bash
git fetch professor
git checkout professor/main -- aulas
```

Detalhes (inclusive como configurar o remoto `professor`) em [COMO-OBTER-AS-ATIVIDADES.md](../COMO-OBTER-AS-ATIVIDADES.md).
