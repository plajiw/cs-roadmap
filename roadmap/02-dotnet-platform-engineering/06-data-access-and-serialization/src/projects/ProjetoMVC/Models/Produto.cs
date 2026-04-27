namespace ProjetoMVC.Models;

public class Produto
{
    public Guid Id { get; set; }
    public string Nome { get; set; }
    public string Categoria { get; set; }
    public string Descricao { get; set; }
    public decimal Preco { get; set; }
    public DateTime DataDeCadastro { get; set; }

    public Produto(string nome, string categoria, string descricao, decimal preco)
    {
        Id = Guid.NewGuid();
        Nome = nome;
        Categoria = categoria;
        Descricao = descricao;
        Preco = preco;
        DataDeCadastro = DateTime.Now;
    }
}