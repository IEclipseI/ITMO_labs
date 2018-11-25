import java.io.*;
import java.util.*;
import java.lang.Math;


public class c {
        static int compare(String str1, String str2) {
            int flag = 0;
            for (int i = 0; i < str1.length(); i++) {
                if (str1.charAt(i) < str2.charAt(i)) {
                        flag = 1;
                }
                if (str1.charAt(i) > str2.charAt(i)) {
                    return -1;
                }
            }
            return flag;

        }
        static boolean saves0(String str) {
            if (str.charAt(0) == '0') {
                return true;
            } else {
                return false;
            }
        }

        static boolean saves1(String str) {
            if (str.charAt(str.length() - 1) == '1') {
                return true;
            } else {
                return false;
            }
        }

        static boolean doubling(String str) {
            if (str.length() == 1) {
                return false;
            }
            boolean ans = true;
            for (int i = 0; i < str.length()/2; i++) {
                if(str.charAt(i) == str.charAt(str.length() - i - 1)) {
                    return false;
                }
            }
            return ans;
        }
                                
        static boolean line(String str) {
            int[] ar = new int [str.length() + 1];
            for (int i = 0; i < str.length(); i++) {
                ar[i] = (int)str.charAt(i);
            }
            for (int i = 1; i < str.length(); i++) {
                for (int j = 0; j < str.length() - i; j++) {
                    ar[j] = (ar[j] + ar[j + 1]) % 2;   
                }
                if (ar[0] == 1) {
                   // System.out.println(i +" "+ (Math.log(i)/Math.log(2)) +"  " + Math.round(Math.sqrt(i)));
                    if (Math.log(i)/Math.log(2) != Math.round(Math.log(i)/Math.log(2))) {
                        return false;
                    }
                }
            }
            return true;
        }

        static boolean monotone(String str) {
            for (int i = 0; i < Math.log(str.length())/Math.log(2); i++) {
                int size = str.length()/(int)Math.pow(2, i);
                for (int j = 0; j < Math.pow(2, i); j++) {
                    //System.out.println(str.substring(j*size, j*size + size/2)+" "+str.substring(j*size + size/2, j*size + size) + " "+compare(str.substring(j*size, j*size + size/2), str.substring(j*size + size/2, j*size + size)));
                    if (compare(str.substring(j*size, j*size + size/2), str.substring(j*size + size/2, j*size + size)) == -1) {
                        return false;
                    }
                }
            }
            return true;
        }

    public static void main(String args[]) {
        boolean saves0 = true;
        boolean saves1 = true;
        boolean doubling = true;
        boolean line = true;
        boolean monotone = true;

        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            String s = in.next();
            s = in.next();
            /*System.out.println(saves0(s));
            System.out.println(saves1(s));
            System.out.println(doubling(s));
            System.out.println(monotone(s));
            System.out.println(line(s)); */
            if (!saves0(s)) {
                saves0 = false;
            }
            if (!saves1(s)) {
                saves1 = false;
            }
            if (!monotone(s)) {
                monotone = false;
            }
            if (!line(s)) {
                line = false;
            }
            if (!doubling(s)) {
                doubling = false;
            }
        }
        if(!(saves0 || saves1 || doubling || line || monotone)) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }        
    }
}
