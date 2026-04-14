using System.Text.Json;
using StackExchange.Redis;

namespace RedisQuickstart.Repositories;

public class RedisRepository : ICacheRepository
{
    private readonly IDatabase _database;
    
    public RedisRepository(IConnectionMultiplexer redis)
    {
        _database = redis.GetDatabase();
    }
    
    public async Task<T?> GetAsync<T>(string key)
    {
        var value = await _database.StringGetAsync(key);
        return value.HasValue ? JsonSerializer.Deserialize<T>(value!) : default;
    }

    public async Task SetAsync<T>(string key, T value, TimeSpan expiration)
    {
        var json = JsonSerializer.Serialize(value);
        await _database.StringSetAsync(key, json, expiration);
    }

    public async Task RemoveAsync(string key) => await _database.KeyDeleteAsync(key);
}