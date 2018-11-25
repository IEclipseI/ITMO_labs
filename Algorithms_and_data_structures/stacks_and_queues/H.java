import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class H {
    public static class Client {
        int time;
        int numb;
        Client(int k, int n) {
            time = k;
            numb = n;
        }
    } 
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("saloon.in"));
        PrintWriter out = new PrintWriter(new File("saloon.out"));
        int n = Integer.parseInt(in.next());
        int[] ar = new int[n];
        //int size = 0;
        ArrayDeque<Client> que = new ArrayDeque<Client>(101);
        for (int i = 0; i < n; i++) {
            Client cl = new Client(in.nextInt()*60 + in.nextInt(), i);
            int temp = in.nextInt();
            //System.out.println(cl.time);
            while (que.size() > 0 && que.peek().time <= cl.time) {
                ar[que.peek().numb] = que.peek().time;
                que.poll();
            }
            if (que.size() > temp) {
                ar[cl.numb] = cl.time;
            } else {
                if (que.size() > 0) {
                    que.add(new Client(que.getLast().time + 20, i));
                } else {
                    que.add(new Client(cl.time + 20, i));
                }
            }        
        }
        //System.out.println(que.size());
        while (que.size() > 0) {
            ar[que.peek().numb] = que.peek().time;
            que.poll();
        }
        for (int i = 0; i < n; i++) {
            out.println(ar[i] / 60 + " " + ar[i] % 60);
        }
        out.close();     
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}