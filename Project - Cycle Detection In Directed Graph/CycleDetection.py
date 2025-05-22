import networkx as nx
import matplotlib.pyplot as plt
import time
import ttkbootstrap as tb
from ttkbootstrap.constants import *
from tkinter import messagebox


class CycleDetectorApp:
    def __init__(self, root):
        self.graph = nx.DiGraph()
        self.root = root
        self.root.title("Directed Graph Cycle Detector")
        plt.ion()  # interactive mode for animation

        self.frame = tb.Frame(root, padding=10)
        self.frame.pack()

        # ── Input fields ──
        tb.Label(self.frame, text="From Node").grid(row=0, column=0, padx=5, pady=5)
        self.from_entry = tb.Entry(self.frame, width=6)
        self.from_entry.grid(row=0, column=1, padx=5)

        tb.Label(self.frame, text="To Node").grid(row=0, column=2, padx=5)
        self.to_entry = tb.Entry(self.frame, width=6)
        self.to_entry.grid(row=0, column=3, padx=5)

        tb.Button(self.frame, text="Add Edge", bootstyle="primary", command=self.add_edge)\
            .grid(row=0, column=4, padx=5)

        # ── Buttons ──
        tb.Button(self.frame, text="Check Cycle (DFS)", bootstyle="info", command=self.check_cycle_dfs)\
            .grid(row=1, column=0, columnspan=2, sticky="ew", pady=5)

        tb.Button(self.frame, text="Check Cycle (Kahn)", bootstyle="warning", command=self.check_cycle_kahn)\
            .grid(row=1, column=2, columnspan=2, sticky="ew", pady=5)

        tb.Button(self.frame, text="Draw Graph", bootstyle="secondary", command=self.draw_graph)\
            .grid(row=2, column=0, columnspan=2, sticky="ew", pady=5)

        tb.Button(self.frame, text="Reset Graph", bootstyle="danger", command=self.reset_graph)\
            .grid(row=2, column=2, columnspan=2, sticky="ew", pady=5)

    def add_edge(self):
        u = self.from_entry.get().strip()
        v = self.to_entry.get().strip()
        if u and v:
            self.graph.add_edge(u, v)
            self.from_entry.delete(0, 'end')
            self.to_entry.delete(0, 'end')
        else:
            messagebox.showerror("Input Error", "Both nodes are required.")

    def check_cycle_dfs(self):
        visited, rec_stack = set(), set()

        def dfs(node, path):
            visited.add(node)
            rec_stack.add(node)
            path.append(node)
            for nbr in self.graph.successors(node):
                if nbr not in visited and dfs(nbr, path):
                    return True
                elif nbr in rec_stack:
                    cycle = path[path.index(nbr):] + [nbr]
                    self.animate_cycle_path(cycle)
                    return True
            path.pop()
            rec_stack.remove(node)
            return False

        for n in self.graph.nodes:
            if n not in visited and dfs(n, []):
                return
        messagebox.showinfo("Result", "No cycle found (DFS).")

    def check_cycle_kahn(self):
        indeg = {u: 0 for u in self.graph.nodes}
        for u in self.graph:
            for v in self.graph.successors(u):
                indeg[v] += 1
        queue = [u for u in indeg if indeg[u] == 0]
        processed = 0
        while queue:
            u = queue.pop(0)
            processed += 1
            for v in self.graph.successors(u):
                indeg[v] -= 1
                if indeg[v] == 0:
                    queue.append(v)
        if processed != len(self.graph):
            msg = ("Cycle exists based on incomplete topological sort.\n"
                   "Note: Kahn’s Algorithm doesn't reveal the exact cycle path; use DFS for path detection.")
            messagebox.showinfo("Cycle Detected (Kahn)", msg)
        else:
            messagebox.showinfo("Result", "No cycle found (Kahn).")

    def draw_graph(self):
        if not self.graph.nodes:
            messagebox.showwarning("Draw Graph", "Graph is empty — nothing to draw.")
            return
        pos = nx.spring_layout(self.graph, seed=42)
        plt.figure(figsize=(6, 4))
        nx.draw(self.graph, pos, with_labels=True,
                node_color='skyblue', edge_color='gray',
                node_size=1500, arrows=True, arrowsize=15, font_weight='bold')
        plt.title("Directed Graph")
        plt.show()

    def animate_cycle_path(self, cycle_path):
        pos = nx.spring_layout(self.graph, seed=42)
        for i in range(len(cycle_path) - 1):
            edge_colors = []
            node_colors = []

            for u, v in self.graph.edges():
                if u == cycle_path[i] and v == cycle_path[i + 1]:
                    edge_colors.append('red')
                else:
                    edge_colors.append('gray')

            for n in self.graph.nodes():
                if n == cycle_path[i] or n == cycle_path[i + 1]:
                    node_colors.append('orange')
                else:
                    node_colors.append('skyblue')

            plt.clf()
            nx.draw(self.graph, pos, with_labels=True,
                    node_color=node_colors, edge_color=edge_colors,
                    node_size=1500, arrows=True, arrowsize=15, font_weight='bold')
            plt.title(f"Cycle Animation: {cycle_path[i]} → {cycle_path[i+1]}")
            plt.pause(1)

        plt.title("Cycle Animation Complete")
        plt.ioff()
        plt.show()

    def reset_graph(self):
        self.graph.clear()
        self.from_entry.delete(0, 'end')
        self.to_entry.delete(0, 'end')
        plt.close('all')
        messagebox.showinfo("Reset", "Graph has been cleared.")


if __name__ == "__main__":
    app = tb.Window(themename="cosmo")  # Modern theme (options: "litera", "darkly", "cyborg", "cosmo", etc.)
    CycleDetectorApp(app)
    app.mainloop()
