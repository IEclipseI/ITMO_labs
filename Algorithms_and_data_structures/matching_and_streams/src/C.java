import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;

@SuppressWarnings("ALL")
public class C {
    public static void main(String[] args) throws IOException {
        StreamFinder streamFinder = new StreamFinder();
        streamFinder.findStream();
    }

    private static class StreamFinder {
        private static final int INF = Integer.MAX_VALUE;

        private List<Vert> g;
        private List<Integer> dist;
        private List<Integer> last;
        private Map<Edge, Edge> map;
        private int n;
        private int m;
        private int s;
        private int t;
        private int maxFlow;

        private void findStream() throws IOException {
            Reader reader = new Reader();
            n = reader.nextInt();
            m = reader.nextInt();
            s = reader.nextInt() - 1;
            t = reader.nextInt() - 1;
            g = new ArrayList<>(n);
            map = new HashMap<>();
            for (int i = 0; i < n; i++) {
                g.add(new Vert(i));
            }
            for (int i = 0; i < m; i++) {
                int from = reader.nextInt(),
                        to = reader.nextInt();
                Edge real = new Edge(from - 1, to - 1, 1, i);
                Edge fake = new Edge(to - 1, from - 1, 0, 0, i + m);
                g.get(from - 1).edges.add(real);
                g.get(to - 1).edges.add(fake);
                map.put(real, fake);
                map.put(fake, real);
            }
            List<List<Integer>> res = dfs();
            if (res.size() < 2) {
                System.out.println("NO");
            } else {
                System.out.println("YES");
                for (int i = 0; i < 2; i++) {
                    for (int v : res.get(i)) {
                        System.out.print(v + 1 + " ");
                    }
                    System.out.println();
                }
            }
        }

        List<List<Integer>> dfs() {
            List<List<Integer>> res = new ArrayList<>();
            maxFlow = 0;
            for (int i = 0; i < 2; i++) {
                makeNotVisited();
                maxFlow += dfsImpl(s);
            }
            if (maxFlow == 2) {
                makeNotVisited();
                List<Integer> path = new ArrayList<>();
                pathDfs(s, path);
                res.add(path);
                makeNotVisited();
                path = new ArrayList<>();
                pathDfs(s, path);
                res.add(path);
                return res;
            } else {
                return res;
            }
        }

        void makeNotVisited() {
            g.forEach(t -> t.isVisited = false);
        }

        boolean pathDfs(int u, List<Integer> path) {
            if (u == t) {
                path.add(u);
                return true;
            }
            path.add(u);
            g.get(u).isVisited = true;
            for (Edge e : g.get(u).edges) {
                if (!g.get(e.to).isVisited && e.flow == 1 && !e.isVisited) {
                    e.isVisited = true;
                    boolean flag = pathDfs(e.to, path);
                    if (flag) {
                        return true;
                    } else {
                        e.isVisited = false;
                    }
                }
            }
            path.remove(path.size() - 1);
            return false;
        }

        int dfsImpl(int u) {
            if (u == t) {
                return 1;
            }
            g.get(u).isVisited = true;
            for (Edge e : g.get(u).edges) {
                if (!g.get(e.to).isVisited && e.flow < e.cap) {
                    int delta = dfsImpl(e.to);
                    if (delta > 0) {
                        e.flow += delta;
                        map.get(e).flow -= delta;
                        return delta;
                    }
                }
            }
            return 0;
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
            boolean isVisited = false;
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
