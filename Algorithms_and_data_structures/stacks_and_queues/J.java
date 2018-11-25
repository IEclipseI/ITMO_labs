import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class J {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("bureaucracy.in"));
        PrintWriter out = new PrintWriter(new File("bureaucracy.out"));
        //BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
        ArrayBlockingQueue<Integer> dq = new ArrayBlockingQueue<Integer>(100000);
        int n = Integer.parseInt(in.next());
        int k = Integer.parseInt(in.next());
        int[] ar = new int[n];
        for (int i = 0; i < n; i++) {
            int tm = in.nextInt();
            ar[i] = tm;
            dq.add(tm);
        }
        int count = n;
        int recieve = 0;
        int crnt = 0;
        Arrays.sort(ar);
        for (int i = 0; i < n; i++) {
            if ((ar[i] - recieve) * count > k) {
                break;
            }
            k = k - ((ar[i] - recieve) * count);
            recieve = ar[i];
            count--;
        }
        //System.out.println(k);
        if (count > 0) {
            recieve += k / count;
            k = k % count;
        }
        //System.out.println(recieve); 
        //System.out.println(count); 

        int size = dq.size();
        for (int i = 0;  i < size; i++) { 
            int tmp = dq.poll(); 
            if (tmp > recieve) {
                dq.add(tmp - recieve);
            }
        }
        //System.out.println(k);
        k = Math.min(k , dq.size());
        for (int i = 0; i < k; i++) {
            int tmp = dq.poll() - 1;
            if (tmp > 0) {
                dq.add(tmp);
            }
        }
        if (dq.size() > 0) {
            out.println(dq.size());
            while (dq.size() != 0) {
                out.print(dq.poll() + " ");
            }
        } else {
            out.println(-1);
        }

                   /**/
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