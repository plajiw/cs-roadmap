# Docker Volumes

Este documento detalha o conceito de volumes no Docker, sua importância para persistência de dados e os métodos de mapeamento.

## Conceitos Fundamentais

### O Problema: Perda de Dados ao Remover Containers

Containers são criados a partir de imagens e possuem uma fina camada de leitura e escrita no topo das camadas de imagem, que são somente leitura e imutáveis. Quando removemos um container com `docker container rm`, essa camada de leitura/escrita é também removida, e **todas as informações contidas nela são perdidas permanentemente**.

Isso cria um problema crítico: como persistir dados de aplicações, logs, código ou banco de dados?

| Problema | Descrição |
|----------|-----------|
| **Perda de dados** | Remover um container deleta todos os dados gerados durante sua execução |
| **Impossibilidade de atualizar** | Não é possível substituir um container sem perder dados associados |
| **Falta de compartilhamento** | Dados não podem ser compartilhados entre containers ou com o host |

### O Volume: Solução para Persistência

**Volumes** são mecanismos Docker para armazenar e persistir dados separando-os do container. Um volume:

- **Separa dados gerados pela aplicação** do armazenamento do container
- **Permite persistência** — dados sobrevivem à remoção do container
- **Facilita compartilhamento** — entre host e container, ou entre múltiplos containers

### Arquitetura: Container, Host e Volume

A relação entre container, Docker host e volume funciona da seguinte forma:

1. O **Docker host** gerencia um **volume** (pasta no sistema de arquivos do host)
2. O **container** monta esse volume em um de seus caminhos internos
3. Toda informação escrita nesse caminho é armazenada no volume do host, não na camada do container
4. Se o container for removido, o volume persiste no host

## Mapeamento de Volumes (Bind Mounts)

### Sintaxe

```bash
docker container run -v <pasta-host>:<pasta-container> <imagem>
```

**Parâmetros:**

| Parâmetro | Descrição |
|-----------|-----------|
| `-v` | Flag para definir um volume (bind mount) |
| `<pasta-host>` | Caminho no host (ex: `$(pwd)/dados` ou `/home/user/dados`) |
| `<pasta-container>` | Caminho dentro do container (ex: `/app/dados`, `/usr/share`) |
| `<imagem>` | Imagem a ser utilizada |

**Exemplo:**

```bash
docker container run -v $(pwd)/teste:/usr/share alpine
```

- `$(pwd)/teste`: Mapeia pasta `teste` do diretório local para o container
- `/usr/share`: Diretório dentro do container onde os dados serão armazenados
- Qualquer arquivo criado em `/usr/share` dentro do container será salvo em `./teste` no host

### Exemplo Prático: Container Alpine com Volume

**Executar container interativo com volume**

```bash
docker container run -it --name alp1 -v $(pwd)/teste:/usr/share alpine
```

**Dentro do container:**

```bash
cd /usr/share
echo 'teste de volume no alpine' > teste.md
```

**No host (em outro terminal):**

```bash
ls teste/
cat teste/teste.md
```

**Resultado:** O arquivo `teste.md` criado dentro do container está disponível na pasta `teste/` do host.

### Verificar Volume em uma Imagem

Use `docker container inspect` para visualizar detalhes do mapeamento:

```bash
docker container inspect alp1
```

**Seção relevante da saída (campo `Mounts`):**

```json
"Mounts": [
  {
    "Type": "bind",
    "Source": "/home/plajiw/teste",
    "Destination": "/usr/share",
    "Mode": "",
    "RW": true,
    "Propagation": "rprivate"
  }
]
```

| Campo | Significado |
|-------|-------------|
| `Type` | Tipo de mount: `bind` (bind mount) ou `volume` (Docker volume) |
| `Source` | Caminho no host (`/home/plajiw/teste`) |
| `Destination` | Caminho no container (`/usr/share`) |
| `RW` | Read/Write — `true` permite leitura e escrita |
| `Propagation` | Política de propagação (`rprivate` = isolado) |

## Principais Usos de Volumes

| Caso de Uso | Descrição |
|-------------|-----------|
| **Persistência de dados** | Manter dados gerados pelo container após sua remoção |
| **Compartilhamento host↔container** | Acessar código-fonte, logs ou dados do host dentro do container |
| **Compartilhamento entre containers** | Múltiplos containers acessam o mesmo volume simultaneamente |
| **Banco de dados** | Persistir dados de aplicações de banco de dados (PostgreSQL, MySQL, Redis) |
| **Desenvolvimento** | Sincronizar código-fonte do host com o container para hot-reload |
