# Operando com Containers

Este documento cobre os comandos essenciais para criar, executar, gerenciar e conectar containers usando a interface de linha de comando do Docker.

## Configuração inicial no Linux

No Linux é necessário configurar permissões para usar Docker sem `sudo` em cada comando:

```bash
sudo groupadd docker
sudo gpasswd -a <user> docker
sudo service docker restart
newgrp docker
```

## Conceitos fundamentais

Docker CLI atua através da API REST do Docker Daemon. Entender a estrutura dos comandos facilita a curva de aprendizado:

```
docker <objeto> <comando> [opções] [argumentos]
```

Exemplos:
- `docker container run` - cria e executa um container
- `docker image pull` - download de imagem
- `docker network ls` - lista redes

## Comando `docker container run`

`docker container run` é a porta de entrada principal no Docker. Internamente realiza 4 operações:

1. **Baixa a imagem** (se não encontrada localmente): `docker image pull`
2. **Cria o container**: `docker container create`
3. **Inicia o container**: `docker container start`
4. **Executa em modo interativo** (se especificado): `docker container exec`

### Exemplo básico

```bash
docker container run hello-world
```

Este comando cria um container a partir da imagem `hello-world` (baixada do Docker Hub se necessário), executa o programa inicial e encerra.

**Referência:** https://hub.docker.com/_/hello-world

### Listar imagens disponíveis

```bash
docker images
```

Exemplo de saída:
```
REPOSITORY      TAG       IMAGE ID       CREATED       SIZE
hello-world     latest    452a468a4bf9   2 weeks ago   20.4kB
```

## Operações essenciais com containers

### Listar containers

| Comando                  | Descrição                                     |
| ------------------------ | --------------------------------------------- |
| `docker container ps`    | Lista containers em execução                  |
| `docker container ps -a` | Lista todos os containers (incluindo parados) |

### Criar e executar

```bash
# Download de imagem específica (sem parâmetro pega a mais recente)
docker image pull alpine
docker image pull alpine:3.18

# Criar e executar container com comando
docker container run alpine ls -l
```

O Docker Engine inicia o container e executa o comando `ls -l` dentro dele.

### Modo interativo

```bash
docker container run -it alpine /bin/sh
```

Opções:
- `-i` (--interactive): Mantém stdin aberto mesmo desconectado
- `-t` (--tty): Aloca pseudo-terminal
- `-it`: Combinação para shell interativo

Isto abre um shell bash dentro do container, permitindo comandos interativos.

### Iniciar container parado

```bash
docker container start <id-ou-nome>
```

### Executar comando em container em execução

```bash
docker container exec <id-ou-nome> ls -l
```

Exemplo com ID completo:
```bash
docker container exec 3b9a5940af6567955054638d94a41df394b5effe95c92fa1f5faaae6c147f5eb ls -l
```

### Parar container

```bash
docker container stop <nome-do-container>
```

Exemplo:
```bash
docker container stop beautiful_poincare
```

## Nomes de containers

### Criar com nome específico

```bash
docker container run --name meu-app alpine
```

**Restrição:** Não é permitido repetir nomes. Cada container deve ter um nome único.

### Remover container

```bash
docker container rm <nome-do-container>
```

Exemplo:
```bash
docker container rm meu-app
```

## Mapeamento de portas

### Motivação

Um container tem como objetivo empacotar e isolar sua aplicação e dependências para poder executar em qualquer lugar. Embora o isolamento seja sua principal característica, um container completamente isolado e inacessível seria pouco útil.

Por isso, podemos **compartilhar recursos** e permitir que o container seja acessado pelo "mundo exterior" através do mapeamento de portas.

### Sintaxe

```bash
docker container run --name <nome> -p <porta-host>:<porta-container> <imagem>
```

**Explicação dos parâmetros:**
- `--name <nome>`: Define nome do container
- `-p <porta-host>:<porta-container>`: Mapeia porta
  - `<porta-host>` (ex: 8080): Porta acessível no host
  - `<porta-container>` (ex: 80): Porta interna do container
- `<imagem>`: Nome da imagem no repositório

### Exemplo prático

```bash
docker container run --name ws1 -p 8080:80 nginx
```

Este comando:
1. Cria um container nomeado `ws1` a partir da imagem `nginx`
2. Mapeia a porta 80 do container (nginx padrão) para porta 8080 do host
3. Qualquer requisição para `http://localhost:8080/` no host é redirecionada para porta 80 dentro do container

### Execução em background

Para executar o container em segundo plano:

```bash
docker container run --name ws1 -p 8080:80 -d nginx
```

Opção:
- `-d` (--detach): Executa em background e retorna o prompt

### Restrições de porta

```bash
# Erro: container com mesmo nome
docker container run --name ws1 -p 8080:80 -d nginx  # ok
docker container run --name ws2 -p 8080:80 -d nginx  # erro: porta 8080 já em uso

# Solução: usar porta diferente
docker container run --name ws2 -p 8081:80 -d nginx  # ok
```

**Restrição:** Não é permitido:
- Repetir nomes de containers
- Mapear dois containers para a mesma porta do host

## Referência rápida de help

```bash
docker --help
docker container run --help
docker container --help
```

## Isolamento entre containers

Um container não tem como interagir com outro container, mesmo que ambos contenham as mesmas imagens. Cada container executa em seu próprio espaço isolado de processo, arquivo e rede. A comunicação entre containers requer configuração explícita de redes Docker.

## Mapeamento de diretórios

### 