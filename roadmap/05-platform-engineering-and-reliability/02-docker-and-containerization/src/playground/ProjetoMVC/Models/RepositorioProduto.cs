
namespace ProjetoMVC.Models
{
    public class RepositorioProduto : IRepositorioProduto
    {
        public IEnumerable<Produto> ObterProdutos()
        {
            return new List<Produto>()
            {
                new Produto("Coca-cola", "Bebidas", 5.99m),
                new Produto("Pão francês", "Padaria", 0.50m),
                new Produto("Leite", "Laticínios", 3.49m),
                new Produto("Arroz", "Mercearia", 2.99m),
                new Produto("Sabonete", "Higiene", 1.25m)
            };
        }
            
    }
}
