import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;

@SuppressWarnings("ALL")
public class G {
    public static void main(String[] args) throws IOException {
        StreamFinder streamFinder = new StreamFinder();
        streamFinder.findStream();
    }

    private static class StreamFinder {
        private static final int INF = Integer.MAX_VALUE / 10000;

        private List<Vert> g;
        private int[] dist;
        private int[] last;
        private Map<Edge, Edge> map;
        private int n;
        private int m;
        private int maxFlow;
        private int s;
        private int t;

        private void findStream() throws IOException {
            Scanner reader = new Scanner(System.in);
            m = reader.nextInt();
            n = reader.nextInt();
            g = new ArrayList<>();
            map = new HashMap<>();
            reader.nextLine();
            StringBuilder sb[] = new StringBuilder[m];
            for (int i = 0; i < m; i++) {
                String line = reader.nextLine();
                sb[i] = new StringBuilder(line);
                for (int j = 0; j < n; j++) {
                    if (sb[i].charAt(j) == 'A') {
                        s = 2 * (i * (n + 1) + j);
                    }
                    if (sb[i].charAt(j) == 'B') {
                        t = 2 * (i * (n + 1) + j) + 1   ;
                    }
                    g.add(new Vert(sb[i].charAt(j)));
                    g.add(new Vert(sb[i].charAt(j)));
                }
                g.add(new Vert('#'));
                g.add(new Vert('#'));
            }

            for (int i = 0; i <= n; i++) {
                g.add(new Vert('#'));
                g.add(new Vert('#'));
            }

            for (int i = 0; i < (n + 1) * (m + 1); i++) {
                addEdge(i);
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    addEdge((n + 1) * i +  j, (n + 1) * i +  j + 1);
                    addEdge((n + 1) * i +  j, (n + 1) * (i + 1) +  j);
                }
            }
            int size = 2 * (n + 1) * (m + 1);
            dist = new int[size];
            last = new int[size];
            for (int i = 0; i < size; i++) {
                dist[i] = 0;
                last[i] = 0;
            }
            maxFlow = 0;
            while (bfs()) {
                Arrays.fill(last, 0);
                int flow = dfs(s, INF);
                while (flow != 0) {
                    maxFlow += flow;
                    flow = dfs(s, INF);
                }
            }
            if (maxFlow >= INF) {
                System.out.println(-1);
            } else {
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        int ind = 2 * ((n + 1) * i +  j);
                        if (ind == s || ind + 1 == t || sb[i].charAt(j) != '.')
                            continue;
                        if (dist[ind + 1] == INF && dist[ind] < INF) {
                            sb[i].setCharAt(j, '+');
                        }
                    }
                }
                System.out.println(maxFlow);
                for (StringBuilder sbder : sb) {
                    System.out.println(sbder.toString());
                }
            }
        }
        int dfs(int u, int minCap) {
            if (u == t || minCap == 0) {
                return minCap;
            }
            for (int v = last[u]; v < g.get(u).edges.size(); v++) {
                if (dist[g.get(u).edges.get(v).to] == dist[u] + 1) {
                    int delta = dfs(g.get(u).edges.get(v).to, Math.min(minCap, g.get(u).edges.get(v).cap - g.get(u).edges.get(v).flow));
                    if (delta != 0) {
                        g.get(u).edges.get(v).flow += delta;
                        map.get(g.get(u).edges.get(v)).flow -=delta;
                        return delta;
                    }
                }
                last[u] = last[u] + 1;
            }
            return 0;
        }

        private boolean bfs() {
            Arrays.fill(dist, INF);
            dist[s] = 0;
            Deque<Integer> queue = new ArrayDeque<>();
            queue.add(s);
            while (!queue.isEmpty()) {
                int u = queue.pollFirst();
                for (Edge e : g.get(u).edges) {
                    if (e.flow < e.cap && dist[e.to] == INF) {
                        dist[e.to] = dist[e.from] + 1;
                        queue.add(e.to);
                    }
                }
            }
            return dist[t] != INF;
        }
//
        enum Type {
            MOUNTAIN, SWAMP, FIELD
        }

        private static class Vert {
            int id;
            boolean isVisited;
            List<Edge> edges;
            Type type;
            static int global_id = 0;

            public Vert(char ch) {
                this.id = global_id++;
                this.isVisited = false;
                this.edges = new ArrayList<>();
                type = ch == '-' || ch == 'A' || ch == 'B' ? Type.SWAMP : (ch == '#' ? Type.MOUNTAIN : Type.FIELD);
            }

            boolean isSwamp() {
                return type.equals(Type.SWAMP);
            }

            boolean isMountain() {
                return type.equals(Type.MOUNTAIN);
            }

            boolean isField() {
                return type.equals(Type.FIELD);
            }

            @Override
            public int hashCode() {
                return id;
            }
        }

        private void addEdge(Vert a, Vert b, int cap) {
            Edge realA = new Edge(a.id, b.id, cap);
            Edge fakeA = new Edge(b.id, a.id, 0);
            a.edges.add(realA);
            b.edges.add(fakeA);
            map.put(realA, fakeA);
            map.put(fakeA, realA);
        }

        private void addEdge(int a, int b) {
            Vert aInp = g.get(a * 2);
            Vert aOut = g.get(a * 2 + 1);
            Vert bInp = g.get(b * 2);
            Vert bOut = g.get(b * 2 + 1);
            if (aInp.isMountain() || bInp.isMountain()) {
                return;
            }
            addEdge(aOut, bInp, INF);
            addEdge(bOut, aInp, INF);
        }

        private void addEdge(int id) {
            Vert a = g.get(id * 2);
            Vert b = g.get(id * 2 + 1);
            if (a.isMountain()) {
                return;
            } else {
                Edge real;
                Edge fake;
                if (a.isField()) {
                    real = new Edge(a.id, b.id, 1);
                    fake = new Edge(b.id, a.id, 0);
                } else {
                    real = new Edge(a.id, b.id, INF);
                    fake = new Edge(b.id, a.id, INF);
                }
                map.put(real, fake);
                map.put(fake, real);
                a.edges.add(real);
                b.edges.add(fake);
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

            public Edge(int from, int to, int cap, int flow, int id, int psevdoCap) {
                this.from = from;
                this.to = to;
                this.cap = cap;
                this.flow = flow;
                this.id = id;
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