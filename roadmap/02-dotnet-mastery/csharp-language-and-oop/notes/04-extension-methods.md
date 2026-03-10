# Extension Methods

## Métodos de Extensão

Métodos de extensão permitem adicionar comportamento a um tipo existente sem modificar seu código-fonte.

Isso é útil quando queremos acrescentar uma operação a um tipo que:

- Não pertence ao projeto, como `string`, `DateTime` ou um tipo de biblioteca externa.
- Não pode ser alterado diretamente.
- Nem sempre vale a pena ser encapsulado em uma subclasse.

## Problema que eles resolvem

Suponha que exista a necessidade de contar quantas linhas existem em uma `string`.

Sem método de extensão, poderíamos escrever algo assim:

```cs
var input = @"A
B
C
D";

int CountLines(string text)
{
	return text.Split(Environment.NewLine).Length;
}

int lineCount = CountLines(input);
```

Funciona, mas a chamada fica menos natural porque a operação está conceitualmente ligada ao valor `input`, e não a uma função solta.

Seria mais expressivo escrever:

```cs
int lineCount = input.CountLines();
```

Como não podemos adicionar esse método diretamente ao tipo `string`, usamos um método de extensão.

## Como declarar

Um método de extensão deve ser declarado:

- Dentro de uma classe estática.
- Como um método estático.
- Com o parâmetro do tipo estendido marcado com `this`.

```cs
public static class StringExtensions
{
	public static int CountLines(this string text)
	{
		return text.Split(Environment.NewLine).Length;
	}
}
```

Uso:

```cs
var input = @"A
B
C
D";

int lineCount = input.CountLines();
```

## Por que a classe precisa ser estática

Métodos de extensão não alteram o tipo original de verdade. Eles são apenas uma forma especial de o compilador permitir uma chamada com sintaxe de instância.

Como esse comportamento não depende de estado interno de objeto, a linguagem exige que o método esteja em uma classe estática e que ele também seja estático.

Ou seja, não existe uma instância de `StringExtensions`. A classe existe apenas para agrupar métodos de extensão.

## Por que o método também precisa ser estático

O método de extensão é, na prática, uma chamada estática comum.

Quando você escreve:

```cs
input.CountLines();
```

o compilador interpreta isso como:

```cs
StringExtensions.CountLines(input);
```

Ou seja, a chamada com sintaxe de instância é apenas açúcar sintático.

## O que significa o `this`

Em métodos de extensão, o `this` no primeiro parâmetro não significa exatamente a mesma coisa que o `this` usado dentro de uma instância de classe.

Aqui, ele funciona como uma marcação especial da linguagem para informar ao compilador que aquele método estático deve poder ser chamado com sintaxe de método de instância.

Em outras palavras, o `this` diz qual é o tipo que será estendido pela sintaxe.

```cs
public static int CountLines(this string text)
```

Nesse caso:

- `string` é o tipo estendido.
- `text` é a instância recebida pelo método.
- O `this` informa ao compilador que esse método pode ser chamado como se fosse um método de instância de `string`.

Ou seja, quando escrevemos:

```cs
input.CountLines();
```

o valor contido em `input` é passado para o parâmetro `text`.

Isso equivale a:

```cs
StringExtensions.CountLines(input);
```

Então, nesse contexto, o parâmetro `text` representa o próprio objeto sobre o qual o método foi chamado.

Se `input` for uma `string`, essa `string` será recebida no parâmetro marcado com `this`.

## O que o `this` representa na prática

O `this` representa a instância do tipo estendido que está participando da chamada.

Exemplo:

```cs
var input = "A\nB\nC";
int lineCount = input.CountLines();
```

Nesse caso:

- `input` é a instância concreta.
- `CountLines()` parece um método da `string`.
- Mas, internamente, `input` é repassado como argumento para o parâmetro `this string text`.

Portanto, o parâmetro com `this` funciona como o receptor da chamada.

Em um método de instância real, esse receptor seria implícito. Em um método de extensão, ele aparece explicitamente como primeiro parâmetro.

## Diferença para o `this` dentro de uma classe

Dentro de uma classe comum, `this` referencia o objeto atual.

Exemplo:

```cs
public class Report
{
	public string Title { get; set; }

	public void PrintTitle()
	{
		Console.WriteLine(this.Title);
	}
}
```

Aqui, `this.Title` significa "a propriedade `Title` do objeto atual".

Já em método de extensão, o `this` não está sendo usado dentro do corpo para acessar o objeto atual. Ele está sendo usado na assinatura do método para dizer: "este método estende esse tipo".

Essa diferença é importante:

- Em método de instância, `this` referencia o objeto atual dentro do corpo do método.
- Em método de extensão, `this` na assinatura define qual parâmetro receberá a instância da chamada.

O parâmetro com `this` deve sempre ser o primeiro parâmetro do método de extensão.

Se houver outros parâmetros, eles vêm depois.

```cs
public static bool HasMinimumLength(this string text, int minLength)
{
	return text.Length >= minLength;
}
```

Uso:

```cs
bool isValid = input.HasMinimumLength(3);
```

Nesse exemplo:

- `input` vai para o parâmetro `this string text`.
- `3` vai para o parâmetro `minLength`.

Ou seja, a chamada:

```cs
input.HasMinimumLength(3);
```

é interpretada como:

```cs
StringExtensions.HasMinimumLength(input, 3);
```

## Importante: o tipo original não foi modificado

Quando usamos método de extensão, não houve alteração real na classe original.

O tipo `string` continua exatamente o mesmo. Apenas passamos a ter uma forma mais expressiva de chamar um método estático externo.

Por isso, também é possível chamar o método assim:

```cs
int lineCount = StringExtensions.CountLines(input);
```

As duas formas funcionam.

## Namespace e visibilidade

Para o método de extensão aparecer na sintaxe `input.CountLines()`, o namespace da classe de extensão precisa estar importado com `using`.

Exemplo:

```cs
using MyProject.Extensions;
```

Sem esse `using`, o método continua existindo, mas pode não aparecer como extensão naquele arquivo.

## Observação prática

Métodos de extensão são úteis quando melhoram legibilidade e organização.

Mas não devem ser usados para esconder lógica complexa demais ou para “simular” alteração real na classe original. O ideal é usá-los em operações pequenas, claras e naturalmente associadas ao tipo estendido.