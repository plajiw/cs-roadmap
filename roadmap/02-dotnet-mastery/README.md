# 02-dotnet-mastery

O objetivo desta trilha nao e apenas estudar C# como linguagem, mas dominar o ecossistema .NET como plataforma de engenharia. Aqui ficam os temas que explicam como o runtime funciona, como o codigo e executado, como aplicacoes ASP.NET Core sao compostas e como o tooling da stack sustenta projetos reais.

Este modulo existe para separar o conhecimento especifico de .NET de outras camadas do roadmap:

- O que e linguagem, runtime, BCL, ASP.NET Core, testes e tooling fica aqui.
- O que e arquitetura, principios, design patterns e clean architecture fica em `03-architecture-design`.
- O que e mensageria, comunicacao distribuida, resiliencia e escala fica em `04-distributed-systems`.
- O que e entrega, operacao, observabilidade, containers e CI/CD fica em `05-platform-reliability`.

## Estrutura recomendada

| Pasta | Foco principal | Exemplos de estudo |
| --- | --- | --- |
| `csharp-language-and-oop` | Fundamentos e recursos avancados da linguagem | tipos, generics, delegates, events, records, pattern matching, encapsulamento, heranca, polimorfismo |
| `collections-and-linq` | Manipulacao de dados em memoria | List, Dictionary, HashSet, IEnumerable, IEnumerator, LINQ, deferred execution, projections, grouping |
| `clr-and-memory` | Entranhas do runtime | CLR, JIT, IL, assemblies, metadata, stack vs heap, GC, boxing, reflection, spans e alocacao |
| `async-and-concurrency` | Fluxo assincro e coordenacao concorrente | Task, async/await, cancellation, TaskScheduler, lock, Monitor, SemaphoreSlim, Channels, parallelism |
| `aspnet-core` | Modelo de aplicacao web da plataforma | hosting, middleware, routing, dependency injection, model binding, filters, auth, minimal APIs |
| `data-access-and-serialization` | Fronteira entre aplicacao e dados externos | ADO.NET, Dapper, EF Core, transactions, change tracking, JSON, System.Text.Json, serialization contracts |
| `testing-and-quality` | Confiabilidade e validacao | xUnit, NUnit, integration tests, mocking, testcontainers, coverage, analyzers, benchmark e qualidade |
| `dotnet-tooling` | SDK e ciclo de vida do projeto | dotnet CLI, csproj, MSBuild, NuGet, solution layout, package versioning, build e publish |

## Regras de separacao

- Se o assunto e modelagem, tipos ou recursos de sintaxe, ele pertence a `csharp-language-and-oop`.
- Se o assunto e colecao, enumeracao ou consulta em memoria, ele pertence a `collections-and-linq`.
- Se o assunto exige entender alocacao, compilacao, metadata ou comportamento interno do runtime, ele pertence a `clr-and-memory`.
- Se o assunto envolve espera, coordenacao entre tarefas, sincronizacao ou throughput, ele pertence a `async-and-concurrency`.
- Se o assunto começa na requisicao HTTP e termina na resposta da aplicacao, ele pertence a `aspnet-core`.
- Se o assunto trata persistencia, query, mapeamento ou trafego de dados serializados, ele pertence a `data-access-and-serialization`.
- Se o assunto valida comportamento, detecta regressao ou mede qualidade tecnica, ele pertence a `testing-and-quality`.
- Se o assunto e sobre SDK, build, pacote, comando ou configuracao de projeto, ele pertence a `dotnet-tooling`.

## Ordem sugerida de estudo

1. `csharp-language-and-oop`
2. `collections-and-linq`
3. `clr-and-memory`
4. `async-and-concurrency`
5. `aspnet-core`
6. `data-access-and-serialization`
7. `testing-and-quality`
8. `dotnet-tooling`

## Estrutura interna de cada modulo

Cada pasta segue o mesmo formato para manter o repositorio limpo e previsivel:

- `summary.md`: vitrine do que foi aprendido.
- `links.md`: referencias rapidas, docs oficiais, videos e benchmarks.
- `notes/`: base de conhecimento com teoria, comparacoes e resumos.
- `src/`: laboratorio isolado para provas de conceito e experimentos.
- `articles/`: rascunhos que podem evoluir para posts tecnicos.

## Como usar esta trilha

- Estude um conceito e registre o raciocinio em `notes/`.
- Crie uma prova pratica minima em `src/` para validar a teoria.
- Consolide os aprendizados em `summary.md`.
- Quando o tema estiver maduro, converta em rascunho publico em `articles/`.

O resultado esperado desta pasta nao e apenas acumulacao de anotacoes. O objetivo e formar um portfolio que prove dominio real de .NET em profundidade: linguagem, runtime, web stack, acesso a dados, testes e tooling.
