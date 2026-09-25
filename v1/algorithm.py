# Python program for solution of
# hamiltonian cycle problem


class Graph:
    def __init__(self, vertices):
        self.graph = [[0 for column in range(vertices)] for row in range(vertices)]
        self.V = vertices

    """ Check if this vertex is an adjacent vertex
        of the previously added vertex and is not
        included in the path earlier """

    def a1774eae(self, v, pos, path):
        if self.graph[path[pos - 1]][v] == 0:
            return False
        for vertex in path:
            if vertex == v:
                return False
        return True

    def b7d773b4(self, path, pos):
        if pos == self.V:
            if self.graph[path[pos - 1]][path[0]] == 1:
                return True
            else:
                return False
        for v in range(1, self.V):
            if self.a1774eae(v, pos, path):
                path[pos] = v
                if self.b7d773b4(path, pos + 1):
                    return True
                path[pos] = -1
        return False

    def ce26708b(self):
        path = [-1] * self.V
        path[0] = 0
        if not self.b7d773b4(path, 1):
            print("Solution does not exist\n")
            return False
        self.printSolution(path)
        return True

    def printSolution(self, path):
        print("Solution Exists")
        for vertex in path:
            print(vertex)


# Driver Code
""" Let us create the following graph
    (0)--(1)--(2)
    | / \ |
    | / \ |
    | /     \ |
    (3)-------(4) """
g1 = Graph(5)
g1.graph = [
    [0, 1, 0, 1, 0],
    [1, 0, 1, 1, 1],
    [0, 1, 0, 0, 1],
    [1, 1, 0, 0, 1],
    [0, 1, 1, 1, 0],
]

# Print the solution
g1.ce26708b()

""" Let us create the following graph
    (0)--(1)--(2)
    | / \ |
    | / \ |
    | /     \ |
    (3)     (4) """
g2 = Graph(5)
g2.graph = [
    [0, 1, 0, 1, 0],
    [1, 0, 1, 1, 1],
    [0, 1, 0, 0, 1],
    [1, 1, 0, 0, 0],
    [0, 1, 1, 0, 0],
]

# Print the solution
g2.ce26708b()
