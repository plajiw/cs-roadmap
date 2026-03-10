# 05-platform-reliability

Este modulo cobre a camada de entrega e operacao de software em ambiente real. O foco aqui nao e a logica de negocio da aplicacao, mas tudo o que permite construir, empacotar, promover, executar, monitorar e manter sistemas de forma confiavel.

Ele complementa as outras trilhas do roadmap:

- `02-dotnet-mastery` explica a plataforma principal de desenvolvimento.
- `03-architecture-design` explica como estruturar software.
- `04-distributed-systems` explica comunicacao, falhas e escala.
- `05-platform-reliability` explica como colocar tudo isso em producao com qualidade operacional.

## Estrutura recomendada

| Pasta | Foco principal | Exemplos de estudo |
| --- | --- | --- |
| `ci-cd` | Automacao de build, test, release e deploy | GitLab CI/CD, runners, stages, jobs, artifacts, cache, environments, deployment strategies |
| `docker-and-containerization` | Empacotamento e execucao isolada de aplicacoes | Dockerfile, images, layers, volumes, networks, multi-stage builds, registries, Compose |
| `infrastructure-as-code` | Infraestrutura declarativa e reproduzivel | Terraform, Pulumi, provisioning, state, modules, remote backends, policy and drift |
| `kubernetes-and-orchestration` | Orquestracao e operacao de workloads distribuidos | Pods, Deployments, Services, Ingress, ConfigMaps, Secrets, Helm, rollout and scaling |
| `observability-and-operations` | Visibilidade, resposta a incidentes e confiabilidade operacional | logs, metrics, traces, alerting, dashboards, SLI, SLO, incident response |

## Regras de separacao

- Se o assunto e pipeline automatizado, integracao continua, entrega continua ou deploy, ele pertence a `ci-cd`.
- Se o assunto e criar imagem, empacotar app, rodar container localmente ou publicar em registry, ele pertence a `docker-and-containerization`.
- Se o assunto e declarar infraestrutura, provisionar recursos ou versionar ambientes, ele pertence a `infrastructure-as-code`.
- Se o assunto e agendar, escalar, expor ou atualizar workloads em cluster, ele pertence a `kubernetes-and-orchestration`.
- Se o assunto e medir saude, diagnosticar falhas, acompanhar sinais operacionais ou responder incidentes, ele pertence a `observability-and-operations`.

## Ordem sugerida de estudo

1. `ci-cd`
2. `docker-and-containerization`
3. `infrastructure-as-code`
4. `kubernetes-and-orchestration`
5. `observability-and-operations`

## Foco atual recomendado

Como seu foco atual e `DSA em C/C++`, `C# Mastery` e `CI/CD com GitLab e Docker`, a progressao mais pragmatica dentro deste modulo e:

1. Dominar `ci-cd` com pipelines reais no GitLab.
2. Conectar o pipeline com `docker-and-containerization` para build e publish de imagens.
3. Avancar para `infrastructure-as-code` e `kubernetes-and-orchestration` quando a entrega automatizada local e em registry estiver madura.

## Estrutura interna de cada modulo

Cada pasta segue o mesmo formato padrao do roadmap:

- `summary.md`: resumo curto do escopo do modulo.
- `links.md`: documentacao oficial, referencias e materiais de apoio.
- `notes/`: teoria, checklists, comparacoes e resumos.
- `src/`: laboratorio pratico com exemplos e provas de conceito.
- `articles/`: rascunhos de conteudo tecnico.

O objetivo desta trilha e mostrar capacidade de entrega de software em nivel profissional: automatizar, empacotar, operar e observar sistemas com consistencia.