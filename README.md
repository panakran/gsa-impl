# Gravitational search algorithm C implementation

## Usage

### terminal parameters

```cmd
gsa -a NumberOfAgents -d Dimension -x Min -X Max -i Iterations -A [Alpha] -G [Gravity] -e [Epsilon] -f Function
```

### parallel execution

```cmd
mpiexec -n 4 ./gsa -a 10 -d 3 -x 1 -X 10 -i 10
```