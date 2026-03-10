# Interface vs Abstract Class

Interface e classe abstrata são formas de abstração, mas não resolvem exatamente o mesmo problema.

As duas permitem trabalhar com contratos mais genéricos, reduzir acoplamento e modelar sistemas orientados a objetos com mais clareza. A diferença principal está no que cada uma representa.

## Interface

Interface representa contrato e comportamento esperado.

Ela é mais apropriada quando o objetivo é dizer que um tipo é capaz de fazer algo, sem afirmar que ele pertence a uma mesma categoria base de objetos.

Em geral, interface está ligada à ideia de:

- O que um objeto pode fazer.
- Como ele se comporta.
- Quais operações ele precisa expor.

Exemplos comuns:

- `IEnumerable`
- `ICollection`
- `IDisposable`
- `IComparable`

Normalmente, o nome da interface expressa capacidade, papel ou contrato. Por isso, é comum aparecer como algo mais próximo de um comportamento do que de uma categoria concreta.

## Classe Abstrata

Classe abstrata representa uma base comum para tipos relacionados.

Ela é mais apropriada quando o objetivo é modelar uma categoria real de objetos que compartilham identidade, estrutura e possivelmente parte da implementação.

Em geral, classe abstrata está ligada à ideia de:

- O que o objeto é.
- O que ele herda como base comum.
- Quais dados e comportamentos já existem na hierarquia.

Ou seja, a classe abstrata não serve apenas para definir contrato. Ela também pode centralizar estado e implementação compartilhada.

## Diferença conceitual principal

- Interface: relação mais próxima de "se comporta como" ou "é capaz de".
- Classe abstrata: relação mais próxima de "é um tipo de".

Exemplo conceitual:

- Um `FileLogger` pode implementar `IDisposable`.
- Um `SqlRepository` também pode implementar `IDisposable`.

Esses dois tipos não precisam pertencer à mesma hierarquia, mas compartilham uma capacidade comum.

Por outro lado:

- `Circle`, `Square` e `Triangle` podem derivar de `Shape`.

Aqui existe uma categoria base clara, o que favorece classe abstrata.

## Comparação prática

### Interface

- Define um contrato.
- Tradicionalmente contém assinatura de membros, sem estado de instância.
- É usada para representar comportamento ou capacidade.
- Não pode ser instanciada.
- Um tipo pode implementar várias interfaces.
- É ideal quando tipos diferentes precisam ser tratados da mesma forma, mesmo sem compartilhar a mesma classe base.

### Classe abstrata

- Define uma base comum para derivação.
- Pode conter membros abstratos e membros com implementação.
- Pode conter estado, como campos e propriedades.
- Pode conter construtores.
- Não pode ser instanciada diretamente.
- Uma classe só pode herdar de uma única classe base.
- É ideal quando existe uma hierarquia real e uma parte da implementação deve ser compartilhada.

## Comparação ponto a ponto

### Implementação

- Interface, no modelo tradicional, não fornece implementação própria dos membros de instância.
- Classe abstrata pode fornecer implementação parcial ou completa para membros não abstratos.

Isso significa que a interface descreve o contrato, enquanto a classe abstrata pode descrever o contrato e também parte do comportamento.

### Estado

- Interface tradicionalmente não armazena estado de instância.
- Classe abstrata pode ter campos, propriedades com lógica, construtores e demais membros compartilhados.

Se existe necessidade de compartilhar dados ou inicialização comum, classe abstrata tende a ser mais adequada.

### Herança e composição de contratos

- Uma classe pode implementar várias interfaces.
- Uma classe só pode herdar de uma classe base.
- Uma interface pode herdar de outra interface.

Esse ponto é central. Interfaces permitem múltiplos contratos. Classes abstratas não resolvem isso, porque a herança entre classes em C# é simples, não múltipla.

### Sobrescrita e obrigatoriedade de implementação

- Em interfaces, os membros exigidos pelo contrato precisam ser implementados pelo tipo concreto, salvo casos de implementação padrão em versões mais novas da linguagem.
- Em classes abstratas, apenas os membros abstratos precisam obrigatoriamente ser sobrescritos nas classes concretas derivadas.

Ou seja, classe abstrata permite mesclar membros obrigatórios e membros opcionais com comportamento padrão.

### Modificadores de acesso e natureza dos membros

No modelo mais clássico de C#:

- Membros de interface são públicos por contrato e não fazem sentido como `sealed` ou `static` no uso tradicional.
- Membros de classe abstrata podem ter diferentes modificadores de acesso, e a classe pode conter membros `static`, `sealed` e não abstratos.

Esse contraste aparece bastante em materiais introdutórios porque ajuda a diferenciar os objetivos das duas abstrações.

## Observação sobre C# moderno

Em versões mais novas do C#, interfaces evoluíram.

Hoje elas podem, em alguns cenários, ter implementação padrão e outros recursos adicionais. Então, afirmações como "interface nunca possui implementação" ou "interface só pode ter assinatura de método" precisam ser entendidas como a regra tradicional e como o modelo mental principal de estudo.

Para aprendizado de orientação a objetos, esse modelo tradicional ainda é o mais útil:

- Interface continua sendo, principalmente, um contrato.
- Classe abstrata continua sendo, principalmente, uma base de herança com possibilidade de implementação compartilhada.

## Exemplo com interface

```cs
public interface ISerializer
{
	string Serialize();
}

public class Invoice : ISerializer
{
	public decimal Total { get; set; }

	public string Serialize()
	{
		return $"Invoice: {Total}";
	}
}

public class AuditLog : ISerializer
{
	public DateTime CreatedAt { get; set; }

	public string Serialize()
	{
		return $"AuditLog: {CreatedAt:O}";
	}
}
```

Nesse caso, `Invoice` e `AuditLog` não precisam ter a mesma classe base. O que importa é que ambos se comportam como `ISerializer`.

## Exemplo com classe abstrata

```cs
public abstract class Shape
{
	public string Name { get; set; }

	public abstract double CalculateArea();

	public void PrintName()
	{
		Console.WriteLine(Name);
	}
}

public class Square : Shape
{
	public double Side { get; set; }

	public override double CalculateArea()
	{
		return Side * Side;
	}
}
```

Aqui existe uma categoria base comum. `Shape` não apenas define contrato, mas também compartilha estrutura e comportamento.

## Quando usar interface

Use interface quando:

- O foco é contrato.
- O foco é capacidade ou comportamento.
- Tipos diferentes precisam ser tratados de forma uniforme.
- O tipo precisa participar de vários contratos ao mesmo tempo.
- Não existe uma hierarquia natural forte entre os objetos.

## Quando usar classe abstrata

Use classe abstrata quando:

- O foco é herança.
- Existe uma categoria base real.
- Há estado compartilhado entre os tipos.
- Existe implementação comum reaproveitável.
- Você quer combinar contrato com comportamento base.

## Regra prática

Se a pergunta for "o que esse objeto é?", geralmente faz mais sentido pensar em classe abstrata.

Se a pergunta for "o que esse objeto consegue fazer?", geralmente faz mais sentido pensar em interface.