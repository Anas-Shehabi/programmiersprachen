/**
 *
 * @author Anas Shehabi
 * @version 1.0
 */

public class Praktikum_02_main  {


        public static void main (String [] args)  {

            char [] arr  = {'H','e','l','l','o'};
            char [] arr2 = {'g','a','l','l','m'};
            char [] arr3 = {'v','e','l','b','o'};
            char [] arr4 = {'p','4','l','2','o'};
            char [] arr5 = {'f','f','i','f','o'};
            Benutzer B1 = new Benutzer( "anas" ,arr);
            Object B2 = new Benutzer("anas",arr);
            Benutzer B4 = new Benutzer( "anas" ,arr);
            Benutzer B5 = new Benutzer( "Rami" ,arr2);
            Benutzer B6 = new Benutzer( "willheim" ,arr3);
            Benutzer B7 = new Benutzer( "Max" ,arr4);
            Benutzer B8 = new Benutzer( "Sandra" ,arr5);


            System.out.println(B1.equals(B2));
            System.out.println(B1.equals(B5));
            System.out.println(B1.equals(B4));



            System.out.println(B1);
            System.out.println(B5);
            System.out.println(B6);
            System.out.println(B7);
            System.out.println(B8);


            BenutzerVerwaltungAdmin admin = new BenutzerVerwaltungAdmin();
            
            try
            {
                admin.benutzerEintragen(B4);
                System.out.println("user hinzugefügt");

            }catch ( NutzerIstBereitVorhanden e) {
                e.printStackTrace();

            }
            try
            {
                admin.benutzerEintragen(B5);
                System.out.println("user hinzugefügt");

            }catch ( NutzerIstBereitVorhanden e) {
                e.printStackTrace();
            }
            try
            {
                admin.benutzerEintragen(B6);
                System.out.println("user hinzugefügt");

            }catch ( NutzerIstBereitVorhanden e) {
                e.printStackTrace();
            }


            System.out.println(admin.benutzerVorhanden(B5));
            System.out.println(admin.benutzerVorhanden(B7));


            try
            {
                admin.benutzerLoeschen(B6);
                System.out.println("user geloscht");

            }catch ( BenutzerIstNichtVorhanden e) {
                e.printStackTrace();
            }

            try
            {
                admin.benutzerLoeschen(B6);
                System.out.println(" user geloscht");

            }catch ( BenutzerIstNichtVorhanden e) {
                e.printStackTrace();
            }


        }
    }


