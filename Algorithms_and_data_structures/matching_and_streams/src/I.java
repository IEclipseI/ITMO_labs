import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;

@SuppressWarnings("ALL")
public class I {
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
        private int maxFlow;
        private int s;
        private int t;


        private void findStream() throws IOException {
//            Reader reader = new Reader("test.txt");
            Scanner reader = new Scanner(System.in);
            map = new HashMap<>();
            n = reader.nextInt();
            s = 0;
            t = n + 1;
            g = new ArrayList<>(n);
            for (int i = 0; i < n + 2; i++) {
                g.add(new Vert(i));
            }
            List<List<Integer>> toPlay = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                toPlay.add(new ArrayList<>());
            }
            List<String> inp = new ArrayList<>();
            List<Integer> scores = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                scores.add(0);
            }
            String tmp = reader.nextLine();
            List<StringBuilder> sb = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                String line = reader.nextLine();
                sb.add(new StringBuilder(line));
                for (int j = 0; j < n; j++) {
                    char ch = line.charAt(j);
                    if (ch == '#')
                        continue;
                    if (ch == '.' && i < j) {
                        toPlay.get(i).add(j);
                    } else if (ch == 'W') {
                        scores.set(i, scores.get(i) + 3);
                    } else if (ch == 'w') {
                        scores.set(i, scores.get(i) + 2);
                    } else if(ch == 'l') {
                        scores.set(i, scores.get(i) + 1);
                    }

                }
            }
            List<Integer> finalScores = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                finalScores.add(reader.nextInt());
            }

            for (int i = 1; i <= n; i++) {
                for (int to : toPlay.get(i - 1)) {
                    Edge real = new Edge(i, to + 1, 3);
                    Edge fake = new Edge(to + 1, i, 0);
                    g.get(i).edges.add(real);
                    g.get(to + 1).edges.add(fake);
                    map.put(real, fake);
                    map.put(fake, real);
                }
            }
            for (int i = 1; i <= n; i++) {
                Edge real = new Edge(s, i, toPlay.get(i - 1).size() * 3);
                Edge fake = new Edge(i, s, 0);
                g.get(s).edges.add(real);
                g.get(i).edges.add(fake);
                map.put(real, fake);
                map.put(fake, real);
            }
            for (int i = 1; i <= n; i++) {
                Edge real = new Edge(i, t, finalScores.get(i - 1) - scores.get(i - 1));
                Edge fake = new Edge(t, i, 0);
                g.get(i).edges.add(real);
                g.get(t).edges.add(fake);
                map.put(real, fake);
                map.put(fake, real);
            }
            dist = new ArrayList<>();
            last = new ArrayList<>();
            for (int i = 0; i <= n + 1; i++) {
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
            for (int i = 1; i <= n; i++) {
                for (Edge e : g.get(i).edges) {
                    if (e.to == s || e.to == t)
                        continue;
                    int flow = e.flow;
                    char ch;
                    if (e.cap != 0) {
                        if (flow == 0) {
                            ch = 'W';
                        } else if (flow == 1) {
                            ch = 'w';
                        } else if (flow == 2) {
                            ch = 'l';
                        } else {
                            ch = 'L';
                        }
                    } else {
                        if (flow == 0) {
                            ch = 'L';
                        } else if (flow == -1) {
                            ch = 'l';
                        } else if (flow == -2) {
                            ch = 'w';
                        } else {
                            ch = 'W';
                        }
                    }
                    sb.get(i - 1).setCharAt(e.to - 1, ch);
                }
            }

            for (StringBuilder sblder: sb) {
                System.out.println(sblder.toString());
            }
//            System.out.println();
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
                        map.get(g.get(u).edges.get(v)).flow -= delta;
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