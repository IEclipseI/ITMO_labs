import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.*;
import java.util.stream.Collectors;

@SuppressWarnings("ALL")
public class A {
    public static void main(String[] args) throws IOException {
        StreamFinder streamFinder = new StreamFinder();
        streamFinder.findStream();
    }

    private static class StreamFinder {
        private static final int INF = Integer.MAX_VALUE;

        private List<Vert> g;
        private List<Integer> dist;
        private List<Integer> last;
        private int n;
        private int m;
        private int maxFlow;

        private void findStream() throws IOException {
            Reader reader = new Reader();
            n = reader.nextInt();
            m = reader.nextInt();
            g = new ArrayList<>(n);
            for (int i = 0; i < n; i++) {
                g.add(new Vert(i));
            }
            for (int i = 0; i < m; i++) {
                int from = reader.nextInt(),
                        to = reader.nextInt(),
                        cap = reader.nextInt();
                g.get(from - 1).edges.add(new Edge(from - 1, to - 1, cap, i));
                g.get(to - 1).edges.add(new Edge(to - 1, from - 1, 0, 0, i + m));
                g.get(to - 1).edges.add(new Edge(to - 1, from - 1, cap,i + 2 * m));
                g.get(from - 1).edges.add(new Edge(from - 1, to - 1, 0,0, i + 3 * m));
            }

            dist = new ArrayList<>(n);
            last = new ArrayList<>(n);
            for (int i = 0; i < n; i++) {
                dist.add(0);
                last.add(0);
            }
            maxFlow = 0;
            while (bfs()) {
                Collections.fill(last, 0);
                int flow = dfs(0, INF);
                while (flow != 0) {
                    maxFlow += flow;
                    flow = dfs(0, INF);
                }
            }
            System.out.println(maxFlow);
            g.stream().map(t -> t.edges).flatMap(List::stream).filter(t -> t.id < m)
                    .sorted(Comparator.comparingInt(t -> t.id)).forEach(t -> System.out.println(t.flow));

        }


        int dfs(int u, int minCap) {
            if (u == n - 1 || minCap == 0) {
                return minCap;
            }
            for (int v = last.get(u); v < g.get(u).edges.size(); v++) {
                if (dist.get(g.get(u).edges.get(v).to) == dist.get(u) + 1) {
                    int delta = dfs(g.get(u).edges.get(v).to, Math.min(minCap, g.get(u).edges.get(v).cap - g.get(u).edges.get(v).flow));
                    if (delta != 0) {
                        g.get(u).edges.get(v).flow += delta;
                        int ind = 0;
                        while (g.get(g.get(u).edges.get(v).to).edges.get(ind).id % m != g.get(u).edges.get(v).id % m)
                            ind++;
                        g.get(g.get(u).edges.get(v).to).edges.get(ind).flow -= delta;
                        return delta;
                    }
                }
                last.set(u, last.get(u) + 1);
            }
            return 0;
        }

        private boolean bfs() {
            Collections.fill(dist, INF);
            dist.set(0, 0);
            Deque<Integer> queue = new ArrayDeque<>();
            queue.add(0);
            while (!queue.isEmpty()) {
                int u = queue.pollFirst();
                for (Edge e : g.get(u).edges) {
                    if (e.flow < e.cap && dist.get(e.to) == INF) {
                        dist.set(e.to, dist.get(e.from) + 1);
                        queue.add(e.to);
                    }
                }
            }
            return dist.get(n - 1) != INF;
        }

        private static class Vert {
            int id;
            boolean isVisited;
            List<Edge> edges;

            public Vert(int id) {
                this.id = id;
                this.isVisited = false;
                this.edges = new ArrayList<>();
            }
        }

        private static class Edge {
            int from;
            int to;
            int cap;
            int flow;
            int id;
            static int global_id = 0;

            public Edge(int from, int to, int cap, int id) {
                this.from = from;
                this.to = to;
                this.cap = cap;
                this.id = id;
                flow = 0;
            }

            public Edge(int from, int to, int cap, int flow, int id) {
                this.from = from;
                this.to = to;
                this.cap = cap;
                this.flow = flow;
                this.id = id;
            }

        }
    }


    static class Reader {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private final byte[] buffer;
        private int bufferPointer, bytesRead;

        public Reader() {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public Reader(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public String readLine() throws IOException {
            byte[] buf = new byte[64];
            int cnt = 0, c;
            while ((c = read()) != -1) {
                if (c == '\n')
                    break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }

        public int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');

            if (neg)
                return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg)
                return -ret;
            return ret;
        }

        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();

            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');

            if (c == '.') {
                while ((c = read()) >= '0' && c <= '9') {
                    ret += (c - '0') / (div *= 10);
                }
            }

            if (neg)
                return -ret;
            return ret;
        }

        private void fillBuffer() throws IOException {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }

        private byte read() throws IOException {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }

        public void close() throws IOException {
            if (din == null)
                return;
            din.close();
        }
    }
}
