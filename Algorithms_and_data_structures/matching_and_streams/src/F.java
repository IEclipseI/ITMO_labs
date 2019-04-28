import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

@SuppressWarnings("ALL")
public class F {
    public static void main(String[] args) throws IOException {
        StreamFinder streamFinder = new StreamFinder();
        streamFinder.findStream();
    }
    private static class StreamFinder {
        private static final int INF = Integer.MAX_VALUE;
        private Map<Edge, Edge> map;
        private List<Vert> g;
        private List<Vert> gCopy;
        private List<Integer> dist;
        private List<Integer> last;
        private List<Edge> edgeList;
        private double[][] lengths;
        private int n;
        private int m;
        private int maxFlow;
        private int s;
        private int t;
        private int size;

        private void findStream() throws IOException {
            Reader reader = new Reader();
            n = reader.nextInt();
            size = n * 2 + 2;
            s = 0;
            t = size - 1;
            g = new ArrayList<>(size);
            g.add(new Vert(0));
            for (int i = 1; i <= n; i++) {
                g.add(new Vert(i, reader.nextDouble(), reader.nextDouble(), reader.nextDouble()));
            }
            for (int i = n + 1; i <= 2 * n; i++) {
                g.add(new Vert(i, reader.nextDouble(), reader.nextDouble()));
            }
            g.add(new Vert(2 * n + 1));
            map = new HashMap<>();
            edgeList = new ArrayList<>();
            for (int i = 1; i <= n; i++) {
                for (int j = n + 1; j <= 2 * n; j++) {
                    double len = distance(g.get(i), g.get(j))/g.get(i).speed;
                    Edge real = new Edge(i, j, len, 1);
                    Edge fake = new Edge(j, i, len, 0);
                    map.put(real, fake);
                    map.put(fake, real);
                    g.get(i).edges.add(real);
                    g.get(j).edges.add(fake);
                    edgeList.add(real);
                }
            }
            for (int i = 1; i <= n; i++) {
                Edge real = new Edge(s, i, 0, 1);
                Edge fake = new Edge(i, s, 0, 0);
                map.put(real, fake);
                map.put(fake, real);
                g.get(s).edges.add(real);
                g.get(i).edges.add(fake);
            }
            for (int i = n + 1; i <= 2 * n; i++) {
                Edge real = new Edge(i, t, 0, 1);
                Edge fake = new Edge(t, i, 0, 0);
                map.put(real, fake);
                map.put(fake, real);
                g.get(i).edges.add(real);
                g.get(t).edges.add(fake);
            }
            edgeList.sort(Comparator.comparingDouble(Edge::getW));
            int a = -1;
            int b = edgeList.size();
            while (a != b - 1) {
                int m = (a + b)/ 2;
                double curW = edgeList.get(m).w;
                copyGraph(curW);
                dist = new ArrayList<>(n + n + 2);
                last = new ArrayList<>(n + n + 2);
                for (int i = 0; i <= n + n + 1; i++) {
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
                if (maxFlow == n) {
                    b = m;
                } else {
                    a = m;
                }
            }
            System.out.println(edgeList.get(b).w);

        }

        void copyGraph(double maxCap) {
            gCopy = new ArrayList<>();

            gCopy.add(new Vert(0));
            for (Edge e : g.get(0).edges) {
                gCopy.get(0).edges.add(e.copy());
            }
            for (int i = 1; i <= 2 * n; i++) {
                gCopy.add(new Vert(i));
                for (Edge e : g.get(i).edges) {
                    if (e.w <= maxCap) {
                        gCopy.get(i).edges.add(e.copy());
                    }
                }
            }
            gCopy.add(new Vert(size - 1));
            for (Edge e : g.get(size - 1).edges) {
                gCopy.get(size - 1).edges.add(e.copy());
            }
//            gCopy.add(g.get(size - 1));
        }

        private double distance(Vert a, Vert b) {
            return Math.sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
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
            for (int v = last.get(u); v < gCopy.get(u).edges.size(); v++) {
                if (dist.get(gCopy.get(u).edges.get(v).to) == dist.get(u) + 1) {
                    int delta = dfs(gCopy.get(u).edges.get(v).to, Math.min(minCap, gCopy.get(u).edges.get(v).cap - gCopy.get(u).edges.get(v).flow));
                    if (delta != 0) {
                        gCopy.get(u).edges.get(v).flow += delta;
                        int ind = 0;
                        while (gCopy.get(gCopy.get(u).edges.get(v).to).edges.get(ind).id / 2 != gCopy.get(u).edges.get(v).id / 2)
                            ind++;
                        gCopy.get(gCopy.get(u).edges.get(v).to).edges.get(ind).flow -= delta;
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
                for (Edge e : gCopy.get(u).edges) {
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
            double speed;
            double x;
            double y;

            public Vert(int id) {
                this.id = id;
                this.isVisited = false;
                this.edges = new ArrayList<>();
            }

            public Vert(int id,  double x, double y) {
                this.id = id;
                this.isVisited = false;
                this.edges = new ArrayList<>();
                this.x = x;
                this.y = y;
            }

            public Vert(int id, double x, double y, double speed) {
                this.id = id;
                this.x = x;
                this.y = y;
                this.speed = speed;
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
            double w;
            static int global_id = 0;

            Edge copy() {
                Edge e = new Edge(from, to, w, cap);
                e.flow = 0;
                e.id = id;
                return e;
            }

            public Edge(int from, int to, double w, int cap) {
                this.from = from;
                this.to = to;
                this.w = w;
                this.id = global_id++;
                flow = 0;
                this.cap = cap;
            }

            public Edge(int from, int to, int cap, int flow, int psevdoCap) {
                this.from = from;
                this.to = to;
                this.cap = cap;
                this.flow = flow;
                this.id = global_id++;
                this.psevdoCap = psevdoCap;
            }

            public double getW() {
                return w;
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
