using Microsoft.EntityFrameworkCore;

namespace ProjetoMVC.Models;

public static class PopularDB
{
    public static void SeedData(IApplicationBuilder app)
    {
        Seed(app.ApplicationServices.GetRequiredService<AppDbContext>());
    }

    private static void Seed(AppDbContext context)
    {
        context.Database.Migrate();

        if (!context.Produtos.Any())
        {
            context.Produtos.AddRange(
                new Produto("Notebook Gamer", "Eletrônicos", "Intel i7, 16GB RAM, RTX 3060", 5499.90m),
                new Produto("Monitor 27 Pol", "Eletrônicos", "4K Ultra HD 144Hz", 1850.00m),
                new Produto("SSD 1TB", "Hardware", "NVMe M.2 Leitura 3500MB/s", 450.00m),
                new Produto("Placa de Vídeo", "Hardware", "NVIDIA RTX 4070 12GB", 4200.00m),
                new Produto("Mouse Gamer RGB", "Periféricos", "12000 DPI Sensor Óptico", 120.00m),
                new Produto("Teclado Mecânico", "Periféricos", "Switch Blue, ABNT2", 280.50m),
                new Produto("Headset Wireless", "Periféricos", "Som Surround 7.1", 560.00m),
                new Produto("Cadeira Ergonômica", "Escritório", "Ajuste de lombar e braços", 1200.00m),
                new Produto("Mesa Stand-Desk", "Escritório", "Ajuste de altura elétrico", 2100.00m),
                new Produto("Luminária LED", "Acessórios", "Controle de temperatura de cor", 89.90m),
                new Produto("Roteador Wi-Fi 6", "Redes", "Dual Band 3000Mbps", 450.00m),
                new Produto("Webcam Full HD", "Acessórios", "1080p com microfone embutido", 199.00m)
            );

            context.SaveChanges();
            Console.WriteLine("Banco de dados populado com sucesso!");
        }
    }
}