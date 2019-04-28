import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

@SuppressWarnings("ALL")
public class D {
    public static void main(String[] args) throws IOException {
        StreamFinder streamFinder = new StreamFinder();
        streamFinder.findStream();
    }
    private static class StreamFinder {
        private static final int INF = Integer.MAX_VALUE;
        private Map<Edge, Edge> map;
        private List<Vert> g;
        private List<Integer> dist;
        private List<Integer> last;
        private int n;
        private int m;
        private int maxFlow;
        private int big = 100000;
        private int s;
        private int t;

        private void findStream() throws IOException {
            Reader reader = new Reader();
            n = reader.nextInt();
            m = reader.nextInt();
            g = new ArrayList<>(n + m + 2);
            map = new HashMap<>();
            g.add(new Vert(0));
            for (int i = 1; i <= n + m; i++) {
                g.add(new Vert(i));
            }
            g.add(new Vert(n + m + 1));
            s = 0;
            t = n + m + 1;
            for (int i = 1; i <= n; i++) {
                int from = i;
                int to = reader.nextInt();
                int cap = 1;
                while (to != 0) {
                    to += n;
                    Edge real = new Edge(from, to, cap);
                    Edge fake = new Edge(to, from, 0, 0, cap);
                    g.get(from).edges.add(real);
                    g.get(to).edges.add(fake);
                    map.put(real, fake);
                    map.put(fake, real);
                    to = reader.nextInt();
                }
            }
            for (int i = 1; i <= n; i++) {
                int cap = 1;
                Edge real = new Edge(s, i, cap);
                Edge fake = new Edge(i, s, 0, 0, cap);
                g.get(s).edges.add(real);
                g.get(i).edges.add(fake);
                map.put(real, fake);
                map.put(fake, real);
            }
            for (int i = n + 1; i <= n + m; i++) {
                int cap = 1;
                Edge real = new Edge(i, t, cap);
                Edge fake = new Edge(t, i, 0, 0, cap);
                g.get(i).edges.add(real);
                g.get(t).edges.add(fake);
                map.put(real, fake);
                map.put(fake, real);
            }

            dist = new ArrayList<>(n + m + 2);
            last = new ArrayList<>(n + m + 2);
            for (int i = 0; i <= n + m + 1; i++) {
                dist.add(0);
                last.add(0);
            }
            maxFlow = 0;
            while (bfs()) {
                Collections.fill(last, 0);
                int flow = dfs(s, INF);
                while (flow != 0) {
                    maxFlow += flow;
                    flow = dfs(s, INF);
                }
            }
            System.out.println(maxFlow);
            List<Edge> mathcing = cut();
            for (Edge e : mathcing) {
                System.out.println(e.from + " " + (e.to - n));
            }
        }

        List<Edge> cut() {
            List<Edge> matching = new ArrayList<>();
            for (int i = 1; i <= n; i++) {
                Vert cur = g.get(i);
                for (Edge e : cur.edges) {
                    if (e.flow == 1) {
                        matching.add(e);
                    }
                }
            }
            return matching;
        }

        int dfs(int u, int minCap) {
            if (u == t || minCap == 0) {
                return minCap;
            }
            for (int v = last.get(u); v < g.get(u).edges.size(); v++) {
                if (dist.get(g.get(u).edges.get(v).to) == dist.get(u) + 1) {
                    int delta = dfs(g.get(u).edges.get(v).to, Math.min(minCap, g.get(u).edges.get(v).cap - g.get(u).edges.get(v).flow));
                    if (delta != 0) {
                        g.get(u).edges.get(v).flow += delta;
                        int ind = 0;
                        while (g.get(g.get(u).edges.get(v).to).edges.get(ind).id / 2 != g.get(u).edges.get(v).id / 2)
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
            dist.set(s, 0);
            Deque<Integer> queue = new ArrayDeque<>();
            queue.add(s);
            while (!queue.isEmpty()) {
                int u = queue.pollFirst();
                for (Edge e : g.get(u).edges) {
                    if (e.flow < e.cap && dist.get(e.to) == INF) {
                        dist.set(e.to, dist.get(e.from) + 1);
                        queue.add(e.to);
                    }
                }
            }
            return dist.get(t) != INF;
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

            @Override
            public int hashCode() {
                return id;
            }
        }

        private static class Edge {
            int from;
            int to;
            int cap;
            int flow;
            int id;
            int psevdoCap;
            static int global_id = 0;

            public Edge(int from, int to, int cap) {
                this.from = from;
                this.to = to;
                this.cap = cap;
                this.id = global_id++;
                flow = 0;
                psevdoCap = cap;
            }

            public Edge(int from, int to, int cap, int flow, int psevdoCap) {
                this.from = from;
                this.to = to;
                this.cap = cap;
                this.flow = flow;
                this.id = global_id++;
                this.psevdoCap = psevdoCap;
            }

            @Override
            public int hashCode() {
                return id;
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
