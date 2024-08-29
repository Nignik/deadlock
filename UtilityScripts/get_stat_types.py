import json

with open("Items.json") as f:
    data = json.load(f)

stats = set()
for _, itemData in data.items():
    for name, stat in itemData.items():
        stats.add(name)
        
for stat in stats:
    print(f'"{stat}", ', end="")