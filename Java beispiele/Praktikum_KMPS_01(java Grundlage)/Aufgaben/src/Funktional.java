
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;

public class Funktional {


    public static Object[] returnVariable(){
        ArrayList<Album> albums = new ArrayList<Album>();
        Boolean is_in_album = false;
        Boolean is_in_track = false;
        int current_album = 0;
        int current_track = 0;
        int current_character = 0;
        ArrayList<String> Ergebnis = new ArrayList<String>();

        return new Object[]{albums, is_in_album,is_in_track,current_album,current_track,current_character,Ergebnis};
    }
   
    public static int Zaeler(byte[] file_contents,int current_character,int length) {

        if (file_contents[current_character + length] == '<') {
                return length;
        }
        return Zaeler(file_contents,current_character,++length);
    }
  
    public static ArrayList<String> createTokenList(byte[] file_contents, Object[] returnVariable){
        ArrayList<Album> albums = (ArrayList<Album>) returnVariable[0];
        Boolean is_in_album = (Boolean) returnVariable[1];
        Boolean is_in_track = (Boolean) returnVariable[2];
        int current_album = (int) returnVariable[3];
        int current_track = (int) returnVariable[4];
        int current_character = (int) returnVariable[5];
        ArrayList<String> Ergebnis = (ArrayList<String>) returnVariable[6];
        if(current_character >= file_contents.length){
            return Ergebnis;
        }
        else if(file_contents[current_character] == '\n' || file_contents[current_character] == '\r' || file_contents[current_character] == '\t'){
            returnVariable[5] = current_character + 1;

        }
        else if(new String(file_contents, current_character, 7, StandardCharsets.UTF_8).equals(new String("<album>"))){
            returnVariable[3] = albums.size();
            albums.add(new Album());
            returnVariable[0] = albums;
            returnVariable[1] = true;
            returnVariable[5] = 7 + current_character;
            Ergebnis.add("album");
        }
        else if(new String(file_contents, current_character, 8, StandardCharsets.UTF_8).equals(new String("</album>"))){
            returnVariable[1] = false;
            returnVariable[5] = 8 + current_character;
            Ergebnis.add("/album");
        }
        else if(new String(file_contents, current_character, 7, StandardCharsets.UTF_8).equals(new String("<title>"))){
            current_character += 7;
            int title_length = Zaeler(file_contents,current_character,0);
            String title = new String(file_contents, current_character, title_length, StandardCharsets.UTF_8);
            returnVariable[5] = current_character + title_length + 8;
            if(is_in_track)
                albums.get(current_album).tracks.get(current_track).title = title;
            else if(is_in_album)
                albums.get(current_album).title = title;
            Ergebnis.add("title");
            Ergebnis.add(title);
            Ergebnis.add("/title");

        }else if(new String(file_contents, current_character, 8, StandardCharsets.UTF_8).equals(new String("<artist>"))){
            current_character += 8;
            int artist_length = Zaeler(file_contents,current_character,0);
            String artist = new String(file_contents, current_character, artist_length, StandardCharsets.UTF_8);
            returnVariable[5] = current_character + artist_length + 9;
            albums.get(current_album).artist = artist;
            Ergebnis.add("artist");
            Ergebnis.add(artist);
            Ergebnis.add("/artist");
        }
        else if(new String(file_contents, current_character, 8, StandardCharsets.UTF_8).equals(new String("<rating>"))){
            current_character += 8;
            int rating_length = Zaeler(file_contents,current_character,0);
            String rating = new String(file_contents, current_character, rating_length, StandardCharsets.UTF_8);
            albums.get(current_album).tracks.get(current_track).rating = Integer.parseInt(rating);
            returnVariable[5] = current_character+rating_length + 9;
            Ergebnis.add("rating");
            Ergebnis.add(rating);
            Ergebnis.add("/rating");
        }else if(new String(file_contents, current_character, 7, StandardCharsets.UTF_8).equals(new String("<track>"))){
            returnVariable[2] = true;
            returnVariable[5] = current_character+8;
            returnVariable[4] = albums.get(current_album).tracks.size();
            albums.get(current_album).tracks.add(new Track());
            Ergebnis.add("track");
        }
        else if(new String(file_contents, current_character, 8, StandardCharsets.UTF_8).equals(new String("</track>"))){
            returnVariable[2] = false;
            returnVariable[5] = current_character + 9;
            Ergebnis.add("/track");
        }
        else if(new String(file_contents, current_character, 9, StandardCharsets.UTF_8).equals(new String("<feature>"))){
            current_character += 9;
            int feature_length = Zaeler(file_contents,current_character,0);
            String feature = new String(file_contents, current_character, feature_length, StandardCharsets.UTF_8);
            albums.get(current_album).tracks.get(current_track).features.add(feature);
            returnVariable[5] = current_character + feature_length + 10;
            Ergebnis.add("feature");
            Ergebnis.add(feature);
            Ergebnis.add("/feature");
        }
        else if(new String(file_contents, current_character, 8, StandardCharsets.UTF_8).equals(new String("<length>"))){
            current_character += 8;
            int length_length = Zaeler(file_contents,current_character,0);
            String length = new String(file_contents, current_character, length_length, StandardCharsets.UTF_8);
            albums.get(current_album).tracks.get(current_track).length = length;
            returnVariable[5] = current_character + length_length + 9;
            Ergebnis.add("length");
            Ergebnis.add(length);
            Ergebnis.add("/length");
        }
        else if(new String(file_contents, current_character, 9, StandardCharsets.UTF_8).equals(new String("<writing>"))){
            current_character += 9;
            int writing_length = Zaeler(file_contents,current_character,0);
            String writing = new String(file_contents, current_character, writing_length, StandardCharsets.UTF_8);
            albums.get(current_album).tracks.get(current_track).writers.add(writing);
            returnVariable[5] = current_character + writing_length + 10;
            Ergebnis.add("writing");
            Ergebnis.add(writing);
            Ergebnis.add("/writing");
        }
        else if(new String(file_contents, current_character, 6, StandardCharsets.UTF_8).equals(new String("<date>"))){
            current_character += 6;
            int date_length =  Zaeler(file_contents,current_character,0);
            String date = new String(file_contents, current_character, date_length, StandardCharsets.UTF_8);
            albums.get(current_album).date = date;
            returnVariable[5] = current_character + date_length + 7;
            Ergebnis.add("date");
            Ergebnis.add(date);
            Ergebnis.add("/date");
        }
        createTokenList(file_contents,returnVariable);
        return Ergebnis;
    }

     public static ArrayList<Album> parseFile( ArrayList<String> Tokenlist, Object[] returnVariable,int i){

       
        ArrayList<Album> albums = (ArrayList<Album>) returnVariable[0];
        Boolean is_in_album = (Boolean) returnVariable[1];
        Boolean is_in_track = (Boolean) returnVariable[2];
        int current_album = (int) returnVariable[3];
        int current_track = (int) returnVariable[4];
      
        
        if(Tokenlist.size() <= i){return albums;}

        else if(Tokenlist.get(i).equals(new String("album"))){
        returnVariable[3] = albums.size();
        albums.add(new Album());
        returnVariable[1] = true;
        }



        
        else if(Tokenlist.get(i).equals(new String("/album"))){
        returnVariable[1] = false;
            
        }


        else if (Tokenlist.get(i).equals(new String("track"))){

            returnVariable[2] = true;
			returnVariable[4] = albums.get(current_album).tracks.size();
			albums.get(current_album).tracks.add(new Track());

            
        }


        else if (Tokenlist.get(i).equals(new String("/track"))){

            returnVariable[2] = false;
        }


        else if(Tokenlist.get(i).equals(new String("title"))){
            String title = new String(return_data(Tokenlist, i+1));
            if(is_in_track)
                albums.get(current_album).tracks.get(current_track).title = title;
            else if(is_in_album)
                albums.get(current_album).title = title;

                i++;    

        }
       
        else if(Tokenlist.get(i).equals(new String("artist"))){
            String artist = new String(return_data(Tokenlist, i+1));
            albums.get(current_album).artist = artist;
            i++;
        }

        else if(Tokenlist.get(i).equals(new String("date"))){
            String date = new String(return_data(Tokenlist, i+1));
            albums.get(current_album).date = date ;
            i++;
            
        }


        else if(Tokenlist.get(i).equals(new String("length"))){
            
            
            String length = new String(return_data(Tokenlist, i+1));
            albums.get(current_album).tracks.get(current_track).length = length;
            i++;
           
        }
        

        else if(Tokenlist.get(i).equals(new String("rating"))){
            
            String rating = new String(return_data(Tokenlist, i+1));
            albums.get(current_album).tracks.get(current_track).rating = Integer.parseInt(rating);
            i++;
        }

        else if(Tokenlist.get(i).equals(new String("writing"))){
           
          String vergleichVar = "/writing";
          getnextfeatureornextwriter(Tokenlist, i, returnVariable,vergleichVar);
        }

        else if(Tokenlist.get(i).equals(new String("feature"))){
           
          String vergleichVar = "/feature";
          getnextfeatureornextwriter(Tokenlist, i, returnVariable,vergleichVar);
           
                    
           
        }



      //  
      parseFile(Tokenlist, returnVariable, ++i);
      return albums;
    
        
        

    }


    public static String return_data(ArrayList<String> Tokenlist, int position){
        return Tokenlist.get(position);
    }

    public static void getnextfeatureornextwriter(ArrayList<String> Tokenlist, int position ,  Object[] returnVariable, String vergleichVar){
        
        ArrayList<Album> albums = (ArrayList<Album>) returnVariable[0];
       // Boolean is_in_album = (Boolean) returnVariable[1];
       // Boolean is_in_track = (Boolean) returnVariable[2];
        int current_album = (int) returnVariable[3];
        int current_track = (int) returnVariable[4];
        String listString = new String(return_data(Tokenlist, position+1));
        
        if(vergleichVar.equals("/feature"))
        {
            if (listString.equals(vergleichVar) ) {
            return;
            }

            else{
            albums.get(current_album).tracks.get(current_track).features.add(listString);
        }
       
        }
        else if (vergleichVar.equals("/writing")) {
            if (listString.equals(vergleichVar) ) {
                return;
                }
    
                else{
                albums.get(current_album).tracks.get(current_track).writers.add(listString);
            }
        }
    
        getnextfeatureornextwriter(Tokenlist, position+1, returnVariable,vergleichVar);
    }



    public static void main(String[] args) throws IOException {
        String file_path = ("alben.xml");
        byte[] file_contents = Files.readAllBytes(Paths.get(file_path));
        ArrayList<String> mylist = createTokenList(file_contents,returnVariable());
        ArrayList<Album> sad = parseFile(mylist, returnVariable(), 0);
        System.out.print(mylist);
        System.out.println();
        for(int i = 0; i < sad.size(); i++){
        System.out.println(sad.get(i));
    }
        
    }
}