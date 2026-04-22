namespace ProjetoMVC.Models
{
    public class Produto
    {
        public Guid Id { get; set; }
        public string Nome { get; set; }
        public string Categoria { get; set; }
        public decimal Preco { get; set; }

        public Produto(string nome, string categoria, decimal preco = 0)
        {
            Id = Guid.NewGuid();
            Nome = nome;
            Categoria = categoria;
            Preco = preco;
        }
    }
}
