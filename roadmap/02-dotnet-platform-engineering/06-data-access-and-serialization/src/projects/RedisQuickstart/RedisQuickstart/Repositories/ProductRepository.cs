using RedisQuickstart.Models;
using StackExchange.Redis;

namespace RedisQuickstart.Repositories;

public class ProductRepository
{
    private readonly List<Product> _data =
    [
        new Product { Id = Guid.NewGuid(), Name = "Product 1", Price = 150.00m },
        new Product { Id = Guid.NewGuid(), Name = "Product 2", Price = 170.00m },
        new Product { Id = Guid.NewGuid(), Name = "Product 3", Price = 89.99m },
        new Product { Id = Guid.NewGuid(), Name = "Product 4", Price = 2357.00m },
        new Product { Id = Guid.NewGuid(), Name = "Product 5", Price = 199.00m },
    ];

    public async Task<Product?> GetByIdAsync(Guid id)
    {
        await Task.Delay(2000); // Simular latência do banco de dados
        return _data.FirstOrDefault(x => x.Id == id);
    }

    public List<Product> GetAll() => _data.ToList();
}