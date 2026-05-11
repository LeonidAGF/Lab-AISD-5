import matplotlib.pyplot as p

trys = []
times = []

with open("Lab-AISD-5/result.txt", "r", encoding="utf-8") as f:
    for line in f:
        line = line.strip()
        if not line or "Benchmark" in line or "-" in line or "[" in line or line=='':
            continue
        str_parts = line.split()
        name = str_parts[0]
        time_ns = int(str_parts[1])
        trys.append(name)
        times.append(time_ns)


p.bar(trys, times)
p.xlabel("Benchmark")
p.ylabel("Time (ns)")
p.title("Benchmark results")
p.show()