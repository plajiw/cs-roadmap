# Abstract Class

## Classe Abstrata

Uma classe abstrata é uma classe que não pode ser instanciada diretamente.

Ela serve como base para outras classes quando existe um comportamento comum, mas também existe a necessidade de obrigar as classes derivadas a implementar parte da lógica.

Uma classe abstrata pode conter:

- Métodos abstratos.
- Métodos concretos com implementação.
- Propriedades, campos e construtores.

```cs
public abstract class ReportExporter
{
  public string FileName { get; set; }

  public void Export()
  {
    Console.WriteLine($"Exportando arquivo: {FileName}");
  }

  public abstract string GenerateContent();
}

public class PdfReportExporter : ReportExporter
{
  public override string GenerateContent()
  {
    return "Conteudo formatado em PDF";
  }
}
```

Nesse exemplo, `ReportExporter` define uma estrutura comum para exportação de relatórios. O método `Export()` já possui implementação, enquanto `GenerateContent()` precisa ser implementado por cada classe derivada de acordo com o formato de saída.

## Método Abstrato

Um método abstrato:

- Não possui implementação.
- Só pode ser declarado dentro de uma classe abstrata.
- Obriga as classes derivadas concretas a fornecerem uma implementação.
- É implicitamente virtual, ou seja, será sobrescrito nas classes derivadas.

Se uma classe herda de uma classe abstrata e não implementa todos os membros abstratos, ela também precisa ser abstrata.

```cs
public abstract class Shape
{
  public abstract double CalculateArea();
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

### Método Abstrato e Método Virtual

- Método abstrato:
  - Não fornece implementação.
  - Obriga a sobrescrita nas classes derivadas concretas.
  - Só existe em classes abstratas.

- Método virtual:
  - Fornece uma implementação padrão.
  - Pode ser sobrescrito nas classes derivadas.
  - Pode existir em classes abstratas ou não abstratas.

```cs
public abstract class Notification
{
  public abstract void Send();

  public virtual void Log()
  {
    Console.WriteLine("Registrando envio...");
  }
}

public class EmailNotification : Notification
{
  public override void Send()
  {
    Console.WriteLine("Enviando e-mail");
  }

  public override void Log()
  {
    Console.WriteLine("Registrando envio de e-mail");
  }
}
```