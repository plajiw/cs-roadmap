using RedisQuickstart.Models;
using RedisQuickstart.Repositories;
using StackExchange.Redis;

namespace RedisQuickstart.Services;

public class ProductService
{
    private readonly ProductRepository _repository;
    private readonly ICacheRepository _cache;
    private const string CachePrefix = "product:";

    public ProductService(ProductRepository repository, ICacheRepository cache)
    {
        _repository = repository;
        _cache = cache;
    }
    
    public async Task<Product?> GetProductAsync(Guid id)
    {
        string cacheKey = $"{CachePrefix}{id}";

        // 1° - Tenta obter do Redis
        var cachedProduct = await _cache.GetAsync<Product>(cacheKey);
        if (cachedProduct != null) return cachedProduct;

        // 2° - Se não houver, busca no banco (500ms)
        var product = await _repository.GetByIdAsync(id);

        // 3° - Se existir no banco, salva no Redis por 5 minutos
        if (product != null)
            await _cache.SetAsync(cacheKey, product, TimeSpan.FromMinutes(5));

        return product;
    }
    
    public List<Product> GetAll() => _repository.GetAll().ToList();
}