var ingredients = new Ingredient[]
{
    new Ingredient { Id = 1, Name = "Flour", Instructions = "Use all-purpose flour for best results." },
    new Ingredient { Id = 2, Name = "Sugar", Instructions = "Granulated sugar works well in cookie recipes." },
    new Ingredient { Id = 3, Name = "Butter", Instructions = "Use unsalted butter for better control over the saltiness." },
    new Ingredient { Id = 4, Name = "Eggs", Instructions = "Large eggs are typically used in baking." },
    new Ingredient { Id = 5, Name = "Chocolate Chips", Instructions = "Semi-sweet chocolate chips are a popular choice." }
};

Console.WriteLine("Create a new cookie recipe! Available ingredients are:");

foreach (var ingredient in ingredients)
    Console.WriteLine($"{ingredient.Id}. {ingredient.Name}");



