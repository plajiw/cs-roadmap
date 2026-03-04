# Classe Abstratas

## Quando e por que usar Métodos Abstratos?

Os métodos abstratos são essenciais quando você quer **definir um contrato obrigatório** que todas as subclasses concretas **devem** cumprir, sem fornecer (ou permitir) uma implementação padrão na classe base.

Principais motivos e cenários de uso:

- **Forçar implementação específica por tipo concreto**  
  Exemplo: Uma classe base `Animal` com método abstrato `FazerSom()`.  
  Nenhuma implementação padrão faz sentido (cada animal faz som diferente), então `Cachorro`, `Gato`, `Pássaro` **devem** implementar obrigatoriamente.

- **Garantir que o design seja completo e seguro**  
  Evita que alguém crie uma subclasse concreta sem implementar comportamentos essenciais, assim o compilador impede a instanciação se faltar implementação.

- **Modelar hierarquias com comportamento obrigatório variado**  
  Exemplos clássicos:
  - `Shape` → `Desenhar()` abstrato (cada forma geométrica desenha de modo diferente)
  - `Pagamento` → `Processar()` abstrato (CartaoCredito, Boleto, Pix implementam de formas distintas)
  - `Veiculo` → `Acelerar()` abstrato (Carro, Moto, BicicletaElétrica têm lógicas diferentes)

- **Promover polimorfismo forte e código mais previsível**  
  Quando você trabalha com referências à classe base (`List<Animal> animais`), sabe que **todo** elemento tem o método `FazerSom()` implementado — sem precisar de verificações em runtime.

## Métodos Abstratos vs. Métodos Virtuais

### Método Abstrado

- **Não possui implementação** na classe onde é declarado (apenas a assinatura).
- **Obrigatoriamente** deve ser implementado por todas as classes derivadas (não-herdadas abstratas).
- É **implicitamente virtual** (não precisa da palavra-chave `virtual`).
- Só pode ser declarado **dentro de classes abstratas** (ou interfaces).
- Força um contrato: garante que toda subclasse concreta terá aquele comportamento definido.

### Método Virtal

- **Possui implementação padrão** na classe base.
- Pode (mas **não é obrigado**) ser sobrescrito nas classes derivadas.
- Requer a palavra-chave `virtual` na declaração.
- Pode ser declarado tanto em **classes abstratas** quanto em **classes concretas** (não abstratas).
- Útil quando você quer oferecer um comportamento padrão, mas permitir customização opcional.

## Resumo: Métodos Abstratos vs. Métodos Virtuais

| Critério                                | Use Método Abstrato                         | Use Método Virtual                                         |
|-----------------------------------------|---------------------------------------------|------------------------------------------------------------|
| Precisa de implementação padrão?        | Não                                         | Sim                                                        |
| Subclasse é **obrigada** a implementar? | Sim                                         | Não (opcional)                                             |
| Onde pode ser declarado?                | Apenas em classes abstratas                 | Em classes abstratas ou concretas                          |
| Objetivo principal                      | Forçar contrato / comportamento obrigatório | Oferecer comportamento padrão + permitir override opcional |
