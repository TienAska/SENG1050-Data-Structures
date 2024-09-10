import random

def read_countries(filename):
    with open(filename, 'r') as file:
        return [line.strip() for line in file if line.strip()]

def generate_couriers_data(countries, num_records):
    data = []
    country_weights = {country: set() for country in countries}
    
    for _ in range(num_records):
        country = random.choice(countries)
        
        # Ensure unique weight for each country
        weight = random.randint(100, 50000)
        while weight in country_weights[country]:
            weight = random.randint(100, 50000)
        country_weights[country].add(weight)
        
        value = round(random.uniform(10, 2000), 2)
        data.append((country, weight, value))
    
    return data

def write_couriers_file(filename, data):
    with open(filename, 'w') as file:
        for country, weight, value in data:
            file.write(f"{country}, {weight}, {value:.2f}\n")

def main():
    countries = read_countries('countries.txt')
    
    if len(countries) < 50:
        print("Warning: Less than 50 countries in the file.")
    
    num_records = random.randint(2000, 5000)
    couriers_data = generate_couriers_data(countries, num_records)
    
    write_couriers_file('couriers.txt', couriers_data)
    print(f"Generated {num_records} records in couriers.txt")

if __name__ == "__main__":
    main()