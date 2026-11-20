-- schema.sql - Cria o banco e a tabela de exemplo (recados).
--
-- Como importar (XAMPP): abra http://localhost/phpmyadmin, clique em "Importar" e escolha este arquivo.
-- Ou, no cmd do Windows:   C:\xampp\mysql\bin\mysql.exe -u root < schema.sql
--
-- Para o seu tema, ADICIONE as suas tabelas abaixo (e pode apagar a de recados quando não precisar mais).
-- Não troque o nome do banco sem avisar a equipe: o servidor usa "projeto_iteam" por padrão
-- (ou a variável de ambiente DB_NOME).

CREATE DATABASE IF NOT EXISTS projeto_iteam
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE projeto_iteam;

CREATE TABLE IF NOT EXISTS recados (
    id          INT UNSIGNED  NOT NULL AUTO_INCREMENT,
    titulo      VARCHAR(100)  NOT NULL,
    mensagem    TEXT          NULL,
    prioridade  TINYINT       NOT NULL DEFAULT 1,
    criado_em   TIMESTAMP     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (id),
    CONSTRAINT ck_recados_prioridade CHECK (prioridade BETWEEN 1 AND 5)
) ENGINE = InnoDB;

-- Dados de exemplo (só entram se a tabela estiver vazia).
INSERT INTO recados (titulo, mensagem, prioridade)
SELECT 'Bem-vindo', 'Este recado veio do banco de dados.', 1 FROM DUAL
WHERE NOT EXISTS (SELECT 1 FROM recados);
