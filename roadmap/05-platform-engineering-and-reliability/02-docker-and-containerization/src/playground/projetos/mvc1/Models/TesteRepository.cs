namespace mvc1.Models
{
    public class TesteRepository : IRepository
    {
        private static Produto[] _produtos = new Produto[]
        {
            new Produto("Produto 1", "Categoria 1", 10.99m) { ProdutoId = 1 },
            new Produto("Produto 2", "Categoria 2", 20.99m) { ProdutoId = 2 },
            new Produto("Produto 3", "Categoria 1", 15.99m) { ProdutoId = 3 },
        };

        public IEnumerable<Produto> Produtos => _produtos;
    }
}