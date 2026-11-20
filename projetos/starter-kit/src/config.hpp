// config.hpp - Configuração do servidor e da conexão com o banco.
//
// Os valores padrão servem para o XAMPP (usuário root, sem senha). Para mudar algo sem alterar o código,
// defina variáveis de ambiente antes de executar o servidor, por exemplo (Windows, cmd):
//     set DB_SENHA=minha_senha
//     set DB_NOME=biblioteca
#pragma once

#include <cstdlib>
#include <string>

struct Config {
    std::string host{"127.0.0.1"};
    unsigned int porta{3306};
    std::string usuario{"root"};
    std::string senha{};
    std::string banco{"projeto_iteam"};

    int portaServidor{8080};

    static Config doAmbiente() {
        Config c;
        c.host = lerTexto("DB_HOST", c.host);
        c.porta = static_cast<unsigned int>(lerNumero("DB_PORTA", static_cast<int>(c.porta)));
        c.usuario = lerTexto("DB_USUARIO", c.usuario);
        c.senha = lerTexto("DB_SENHA", c.senha);
        c.banco = lerTexto("DB_NOME", c.banco);
        c.portaServidor = lerNumero("PORTA", c.portaServidor);
        return c;
    }

private:
    static std::string lerTexto(const char* nome, const std::string& padrao) {
        const char* valor = std::getenv(nome);
        return valor != nullptr ? std::string(valor) : padrao;
    }

    static int lerNumero(const char* nome, int padrao) {
        const char* valor = std::getenv(nome);
        if (valor == nullptr) {
            return padrao;
        }
        char* fim = nullptr;
        long convertido = std::strtol(valor, &fim, 10);
        return (fim != valor && *fim == '\0') ? static_cast<int>(convertido) : padrao;
    }
};
