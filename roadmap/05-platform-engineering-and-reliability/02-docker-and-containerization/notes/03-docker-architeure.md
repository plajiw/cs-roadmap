# Arquitetura do Docker

O ecossistema Docker segue um modelo cliente-servidor robusto e bem definido.

## Componentes principais

**Cliente (Docker CLI):** Interface de linha de comando que envia comandos ao Docker Daemon.

**Docker Daemon (Docker Engine):** Serviço responsável pelo trabalho pesado:
- Criar imagens e containers
- Executar containers
- Gerenciar redes e volumes
- Distribuir containers a partir de imagens obtidas no registry

**Registry:** Repositório centralizado de imagens (Docker Hub, registries privados, GitHub Container Registry, Amazon ECR, Azure Container Registry, etc.).

**Objetos Docker:** Entidades gerenciadas pelo Engine (imagens, containers, redes, volumes, serviços).

## Fluxo de execução

```
Registry (Repositórios de imagens)
    ↓
Host baixa a imagem do repositório
    ↓
Criamos container a partir da imagem
    ↓
Acessamos e executamos a aplicação
```

## Benefícios da arquitetura

| Benefício                         | Descrição                                                              |
| --------------------------------- | ---------------------------------------------------------------------- |
| **Velocidade de boot**            | Inicialização rápida de containers                                     |
| **Velocidade de deploy**          | Distribuição ágil de aplicações                                        |
| **Economia de recursos**          | Compartilhamento eficiente do kernel                                   |
| **Execução em background**        | Processos do container rodam isolados no sistema host                  |
| **Concorrência**                  | Múltiplos containers simultâneos sem conflito                          |
| **Flexibilidade de configuração** | Fácil modificar infraestrutura sem alterar código                      |
| **Portabilidade**                 | Uma vez criado, executa em qualquer lugar onde Docker esteja instalado |

## Fluxo de comunicação

O cliente conversa com o Docker daemon através da API REST. O daemon faz o trabalho de criar, executar e distribuir os containers a partir de imagens obtidas no registry. Esse design desacoplado permite:

- Remotizar o daemon (executar em servidor diferente).
- Automatizar operações via API.
- Integrar com orquestradores e CI/CD.