import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;

import static java.lang.Math.*;

@SuppressWarnings("ALL")
public class J {
    public static void main(String[] args) throws IOException {
        StreamFinder streamFinder = new StreamFinder();
        streamFinder.findStream();
    }

    private static class StreamFinder {
        private static final long INF = Long.MAX_VALUE;

        private List<Vert> g;
        private List<Long> dist;
        private List<Integer> last;
        private int n;
        private long m;
        private long maxFlow;
        private int s;
        private int t;

        private long dist(Vert a, Vert b) {
            long h = (a.x1 <= b.x1) ? b.x1 - a.x2 : a.x1 - b.x2;
            long v = (a.y1 <= b.y1) ? b.y1 - a.y2 : a.y1 - b.y2;
            long ans = max(v, h);
            if (ans < 0) {
                ans = 0;
            }
            return ans;
        }

        private void findStream() throws IOException {
            Reader reader = new Reader();
            n = reader.nextInt();
            long w = reader.nextLong();
            g = new ArrayList<>();
            s = 0;
            t = n + 1;
            dist = new ArrayList<>();
            for (int i = 0; i <= n + 1; i++) {
                dist.add(0l);
            }
            g.add(new Vert(0, -10_000_000_000l, w, 10_000_000_000l, w));
            for (int i = 1; i <= n; i++) {
                g.add(new Vert(i, reader.nextLong(), reader.nextLong(), reader.nextLong(), reader.nextLong()));
            }
            g.add(new Vert(n + 1, -10_000_000_000l, 0, 10_000_000_000l, 0));
            Collections.fill(dist, INF);
            dist.set(s, 0l);
            for (int i = 0; i <= n + 1; i++) {
                Vert v = null;
                for (int j = 0; j <= n + 1; j++) {
                    if (!g.get(j).isVisited && (v == null || dist.get(j) < dist.get(v.id))) {
                        v = g.get(j);
                    }
                }
                if (dist.get(v.id) == INF) {
                    break;
                }
                v.isVisited = true;
                for (Vert u : g) {
                    if (v != u) {
                        long p = dist(v, u);
                        if (dist.get(v.id) +  p < dist.get(u.id))
                            dist.set(u.id, dist.get(v.id) + p);
                    }
                }
            }
            System.out.println(dist.get(t));
        }

        private static class Vert {
            int id;
            long x1;
            long y1;
            long x2;
            long y2;
            boolean isVisited;
            List<Edge> edges;

            public Vert(int id, long x1, long y1, long x2, long y2) {
                this.id = id;
                this.x1 = x1;
                this.y1 = y1;
                this.x2 = x2;
                this.y2 = y2;
                isVisited = false;
                edges = new ArrayList<>();
            }
        }

        private static class Edge {
            int from;
            int to;
            long w;
            static int global_id = 0;

            public Edge(int from, int to, long w) {
                this.from = from;
                this.to = to;
                this.w = w;
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
