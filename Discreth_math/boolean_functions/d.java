import java.io.*;
import java.util.*;
import java.lang.Math;


public class d {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
            int n = in.nextInt();
            long[] ar = new long[n]; 
            for (int i = 0; i < n; i++) {
                ar[i] = in.nextLong();
            }
            StringBuilder sbr = new StringBuilder();
            long tmp = in.nextLong();
            if (tmp == 0) {
                sbr.append(1);
                sbr.append('&');
                sbr.append('~');
                sbr.append(1);
                System.out.print(sbr.toString());
                return;
            }
            long res = 0; 
            String ans = Long.toString(tmp, 2);
            int[] arans = new int[ans.length()];
            StringBuilder str0 = new StringBuilder();
            for (int i = 0; i < Long.toString(tmp, 2).length(); i++) {
                str0.append('0');
            }                   
            for (int i = 0; i < ans.length(); i++) {
                if (ans.charAt(ans.length() - 1 - i) == '1') {
                    arans[i] = 1;
                }
            }
            for (int i = 0; i < ans.length(); i++) {
                if (arans[i] == 1) {
                    long kon = Long.MAX_VALUE;
                    for (int j = 0; j < n; j++) {
                        String s = Long.toString(ar[j], 2);
                        if (str0.length() - s.length() >=0) {
                            s = str0.substring(0, str0.length() - s.length()) + s;
                        }
                        //System.out.println(s);
                        if (s.charAt(s.length() - 1 - i) == '1') {
                            sbr.append(j + 1);
                            kon = kon & ar[j];
                        } else {
                            kon = kon & ~ar[j];
                            sbr.append('~');
                            sbr.append(j + 1);
                        }
                        if (j != n - 1) {
                            sbr.append('&');
                        }
                        //System.out.println(kon);
                    }
                    res = res | kon;
                    if (i != ans.length() - 1) {
                        sbr.append('|');
                    }
                }
            }
            if (res != tmp) {
                System.out.print("Impossible");
            } else {
                System.out.print(sbr.toString());
            }
            /*System.out.println(saves0(s));
            System.out.println(saves1(s));
            System.out.println(doubling(s));
            System.out.println(monotone(s));
            System.out.println(line(s)); */
                
    }
}
