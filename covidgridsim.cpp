#include <iostream>
#include <string>
#include <cstdlib>//κάνουμε include την cstdlib για να μπορούμε να χρησιμοποιήσουμε την rand και να παράγουμε τυχαίες τιμές
#include <ctime>//κάνουμε include την ctime για να βάλουμε το time(0) στην srand για να προσομοιώσουμε την τυχαιότητα των τιμών
#include <math.h>//κάνουμε include την math.h για τον υπολογισμό αποστάσεων και συγκρίσεων με την ακτίνα σε συγκεκριμένες συναρτήσεις
#include <limits>//κάνουμε include την limits για να διαχεριστούμε τα exceptions
using namespace std;

template<class T>
struct node {   //φτιάχνουμε την δομή node όπου αποτελεί τα δεδομένα που θα πρέπει να περιέχει κάθε κόμβος
public:
    node<T>* next;// τον pointer next που θα δείχνει στην διεύθυνση του επόμενου κόμβου
    node<T>* first;// τον pointer first που θα δείχνει στον πρώτο κόμβο
    T x;//την μεταβλητή x όπου θα περιέχει την συντεταγμένη x ενός χρήστη
    T y;//την μεταβλητή y όπου θα περιέχει την συντεταγμένη y ενός χρήστη
    T time;//την μεταβλητή time όπου θα περιέχει την ώρα που δημιουργήθηκε ο κόμβος
};

template<class T>
class LinkedList    //Δημιουργούμε την τάξη LinkedList όπου ουσιαστικά μέσω αυτής θα μας επιτραπεί η δημιουργία κόμβων
{
public:
    node<T>* first; //ορίζουμε τον Pointer first όπου θα δείχνει στον πρώτο κόμβο της αλυσίδας
    node<T>* last;//ορίζουμε τον Pointer last όπου θα δείχνει στον τελευταίο κόμβο της αλυσίδας
    node<int> *healthy1ptr[1000];//ορίζουμε ένα πίνακα όπου θα περιέχει μέσα τις διευθύνσεις που θα δείχνουν στον πρώτο κόμβο κάθε νέας ημέρας(π.χ. healthy1ptr[2] θα περιέχει τον πρώτο κόμβο της ημέρας 2)
    node<int> *infected1ptr[1000];//αντίστοιχα φτιάχνουμε έναν για κάθε χρήστη που έχουμε και τους αρχικοποιούμε με μέγεθος 1000 που είναι ένας μεγάλος αριθμός που για να γεμίσουν θα πρέπει ο χρήστης να τρέχει το πρόγραμμα για πάνω από 10000 μέρες που υποθέτουμε ότι δε θα γίνει
    node<int> *infected2ptr[1000];
    node<int> *healthy2ptr[1000];

    LinkedList<T>() {//ο constructor της τάξης LinkedList
        first = NULL;//αρχικοποιούμε το first με NULL
        last = NULL;//αρχικοποιούμε το last με NULL
    }

//Συνάρτηση Insert που εισάγει στην προηγούμενη θέση της λίστας που δίνουμε ως όρισμα έναν κόμβο με δεδομένα του χρήστη
    void Insert(int pos, T ix, T iy, T itime,node<int> *ptr)//ως ορίσματα παίρνει την θέση στην οποία θέλουμε να εισάγουμε στην προηγούμενη από αυτή τον κόμβο,την συντεταγμένη x, την συντεταγμένη y,την ώρα ,και τον πίνακα με τις διευθύνσεις που δείχνουν στον πρώτο κόμβο μίας ημέρας
  {
    // δημιουργούμε 3 pointers για την υλοποίηση της Insert
    node<T> *pre=new node<T>;//έναν που δείχνει στον προηγούμενο κόμβο από αυτόν που βρισκόμαστε
    node<T> *cur=new node<T>;//έναν που δείχνει στον κόμβο που βρισκόμαστε
    node<T> *temp=new node<T>;// έναν που θέλουμε να βάλουμε ανάμεσα από αυτούς τους δύο
    cur=ptr;//ορίζουμε ώς την τωρινή θέση μας την διεύθυνση του πρώτου κόμβου της ημέρας στην οποία βρισκόμαστε
    for(int i=1;i<pos;i++)//ψάχνουμε μέσω του βρόχου αυτού την θέση στην οποία θέλουμε να βρεθούμε (το pos)
    {
      pre=cur;
      cur=cur->next;//μέσω του next προχωράμε στην λίστα κατά την σειρά με την οποία είχαμε κάνει add τους χρήστες
    }
    //όταν βρεθούμε στην σωστή θέση
    temp->x=ix;//μέσω του temp που δείχνει πλέον στην σωστή θέση της λίστας βάζουμε τα ορίσματα του χρήστη δηλαδή τη συντεταγμένη x
    temp->y=iy;// την y
    temp->time=itime;// την ώρα time
    pre->next=temp;	//κάνουμε τον next pointer του προηγούμενου κόμβου από τον current να δείχνει τώρα στην temp
    temp->next=cur;//και κάνουμε τον next pointer της temp να δείχνει τώρα στην current και έτσι καταφέραμε να εισάγουμε έναν καινούριο κόμβο ανάμεσα στον previous και στον current
  }

//Συνάρτηση Delete που δίνουμε ώς όρισμα την θέση στη λίστα και διαγράφει τον κόμβο πίσω από την θέση που δώσαμε
    void Delete(int pos,node<int> *ptr){//διαγράφει τον κόμβο στο position-1
        node<T> *pre=new node<T>;//pointer που δείχνει στον προηγούμενο κόμβο από αυτόν που βρισκόμαστε
        node<T> *cur=new node<T>;//pointer που δείχνει στον κόμβο που βρισκόμαστε
        cur = ptr;//ορίζουμε ώς την τωρινή θέση μας την διεύθυνση του πρώτου κόμβου της ημέρας στην οποία βρισκόμαστε
        for(int i=1;i<pos;i++){//ψάχνουμε μέσω του βρόχου αυτού την θέση στην οποία θέλουμε να βρεθούμε (το pos)
            pre=cur;
            cur=cur->next;//μέσω του next προχωράμε στην λίστα κατά την σειρά με την οποία είχαμε κάνει add τους χρήστες
        }
        pre->next=cur->next;//ουσιαστικά όταν βρούμε την θέση που θέλουμε να διαγράψουμε αλλάζουμε τον pointer next να δείχνει στον next του current κόμβου ώστε να προσπεράσουμε αυτόν και να φαίνεται σαν να τον διαγράψαμε από την λίστα
    }

//Συνάρτηση που προσθέτει στο τέλος της λίστας έναν κόμβο με τα στοιχεία του χρήστη
    void add(T x, T y, T time) {//ως ορίσματα παίρνει τις συντεταγμένες x,y του χρήστη και την ώρα time που βρισκόμαστε
        //Σε περίπτωση που η λίστα είναι άδεια
        if (!first) {//καταλαβαίνουμε ότι η λίστα είναι άδεια αν ο δείκτης first έχει ακόμη την τιμή NULL από τον constructor
            first = new node<T>;//έτσι δημιουργούμε έναν νέο κόμβο
            first->x = x;//και βάζουμε μέσα τη συντεταγμένη x
            first->y = y;//την y
            first->time = time;//την ώρα time
            first->next = NULL;//και κάνουμε τον δείκτη next να πάρει τιμή NULL δηλαδή να δείχνει στην διεύθυνση ενός κενού κόμβου στον οποίο θα βάλουμε στοιχεία μετά
            last = first;//και ορίζουμε το last=first για να δείξουμε που τελειώνει η λίστα στη συγκεκριμένη περίπρωση εφόσον είναι άδεια το last=first 
        }
        else {
            //Σε περίπτωση που δεν είναι άδεια η λίστα δηλαδή έχει ήδη ένα κόμβο
            if (last == first) {//αυτό το καταλαβαίνουμε αν last = first ότι η λίστα έχει μόνο έναν κόμβο
                last = new node<T>;// δημιουργούμε έναν καινούριο κόμβο
                last->x = x;//και βάζουμε μέσα τη συντεταγμένη x
                last->y = y;//την y
                last->time = time;//την ώρα time
                last->next = NULL;//και κάνουμε τον δείκτη next να πάρει τιμή NULL δηλαδή να δείχνει στην διεύθυνση ενός κενού κόμβου στον οποίο θα βάλουμε στοιχεία μετά
                first->next = last;//και βάζουμε τον δείκτη next του πρώτου κόμβου να δείχνει στην διεύθυνση last δηλαδή συνδέουμε τον πρώτο με τον δεύτερο κόμβο
            }
            else {
                // Σε περίπτωση που η λίστα τώρα έχει παραπάνω από ένα κόμβο
                node<T>* nextnode = new node<T>;// δημιουργούμε έναν καινούριο κόμβο
                nextnode->x = x;//και βάζουμε μέσα τη συντεταγμένη x
                nextnode->y = y;//την y
                nextnode->time = time;//την ώρα time
                nextnode->next = NULL;;//και κάνουμε τον δείκτη next να πάρει τιμή NULL δηλαδή να δείχνει στην διεύθυνση ενός κενού κόμβου στον οποίο θα βάλουμε στοιχεία μετά
                last->next = nextnode;//και βάζουμε τον δείκτη next του προηγούμενου κόμβου να δείχνει στην διεύθυνση nextnode δηλαδή συνδέουμε τον προηγούμενο με τον επόμενο κόμβο
                last = nextnode;//και ορίζουμε το last=nextnode για να δείξουμε που τελειώνει η λίστα
            }
        }
    }

//Συνάρτηση που ο χρήστης δίνει ώς όρισμα την θέση και τον pointer της ημέρας στην οποία βρίσκεται και του επιστρέφεται η συντεταγμένη x της θέσης του κόμβου εκείνου
    T getX(int index,node<int> *ptr) {
        if (index == 0) {//αν η θέση που έδωσε ο χρήστης αντιστοιχεί στο 0 τότε γυρνάμε τη συντεταγμένη x που βρίσκεται στη διεύθυνση που δείχνει δείκτης
            return ptr->x;
        }
        else {
            // Αλλιώς παίρνουμε το index'οστό στοιχείο
            node<T>* curr = ptr;//ορίζουμε ώς την τωρινή θέση μας την διεύθυνση του πρώτου κόμβου της ημέρας στην οποία βρισκόμαστε
            for (int i = 0; i < index; ++i) {//ψάχνουμε μέσω του βρόχου αυτού την θέση στην οποία θέλουμε να βρεθούμε (το index)
                curr = curr->next;//μέσω του next προχωράμε στην λίστα κατά την σειρά με την οποία είχαμε κάνει add τους χρήστες
            }
            return curr->x;//όταν φτάσουμε στον index τότε επιστρέφουμε στον χρήστη την συντεταγμένη x που είναι μέσα στον κόμβο εκείνο
        }
    }

//Συνάρτηση που ο χρήστης δίνει ώς όρισμα την θέση και τον pointer της ημέρας στην οποία βρίσκεται και του επιστρέφεται η συντεταγμένη y της θέσης του κόμβου εκείνου(ίδια με την getX απλά για y)
    T getY(int index,node<int> *ptr) {
        if (index == 0) {
            //αν η θέση που έδωσε ο χρήστης αντιστοιχεί στο 0 τότε γυρνάμε τη συντεταγμένη y που βρίσκεται στη διεύθυνση που δείχνει δείκτης
            return ptr->y;
        }
        else {
            // Αλλιώς παίρνουμε το index'οστό στοιχείο
            node<T>* curr = ptr;//ορίζουμε ώς την τωρινή θέση μας την διεύθυνση του πρώτου κόμβου της ημέρας στην οποία βρισκόμαστε
            for (int i = 0; i < index; ++i) {//ψάχνουμε μέσω του βρόχου αυτού την θέση στην οποία θέλουμε να βρεθούμε (το index)
                curr = curr->next;
            }
            return curr->y;//όταν φτάσουμε στον index τότε επιστρέφουμε στον χρήστη την συντεταγμένη y που είναι μέσα στον κόμβο εκείνο
        }
    }

//Συνάρτηση που ο χρήστης δίνει ώς όρισμα την θέση και τον pointer της ημέρας στην οποία βρίσκεται και του επιστρέφεται η ώρα time της θέσης του κόμβου εκείνου
    T getTime(int index,node<int> *ptr) {
        if (index == 0) {
            //αν η θέση που έδωσε ο χρήστης αντιστοιχεί στο 0 τότε γυρνάμε τη συντεταγμένη y που βρίσκεται στη διεύθυνση που δείχνει δείκτης
            return ptr->time;
        }
        else {
            // Αλλιώς παίρνουμε το index'οστό στοιχείο
            node<T>* curr = ptr;//ορίζουμε ώς την τωρινή θέση μας την διεύθυνση του πρώτου κόμβου της ημέρας στην οποία βρισκόμαστε
            for (int i = 0; i < index; ++i) {//ψάχνουμε μέσω του βρόχου αυτού την θέση στην οποία θέλουμε να βρεθούμε (το index)
                curr = curr->next;
            }
            return curr->time;//όταν φτάσουμε στον index τότε επιστρέφουμε στον χρήστη την ώρα time που είναι μέσα στον κόμβο εκείνο
        }
    }

//Συνάρτηση που επιστρέφει true αν ο χρήστης παρέμεινε εντός ακτίνας R σε μία περοχή κοντά στους Infected για τουλάχιστον Τ1 χρόνο και ύστερα από Τ2 χρόνο
    bool POSSIBLE_COVID_19_INFECTION(LinkedList User, int Day, LinkedList Infected, LinkedList Infected2,node<int> *ptr[]) {//παίρνει ως ορίσματα τον χρήστη που ελέγχουμε, την ημέρα, τους 2 Infected και τον δείκτη που δείχνει στον πρώτο κόμβο της ημέρας 
        //συνθήκη=αν ο χρήστης βρέθηκε εντός ακτίνας R
        int R = 5;      //Ακτίνα
        int T1 = 900;   //15 mins = 900 seconds
        int T2 = 14400; //4 hours = 14400 seconds
        int u = 0;      //Χρησιμοποιώ αυτήν την μεταβλητή ώστε να ελέγξω αν η συνθήκη θα ισχύσει τις τελευταίες Τ2 ώρες της ημέρας
        int t;          //Χρησιμοποιώ αυτήν την μεταβλητή ώστε να ελέγξω για πόση ώρα θα ισχύει η συνθήκη
        int i;          //μετρητής
        int k;          //νέος μετρητής
        //Έλεγχος χρήστη με τον πρώτο infected
        for (i = 0; i <= 2880 - T2 / 30; i++) {     //Ελέγχω αν ισχύει η συνθήκη για τις πρώτες 24-Τ2 ώρες
            k = i;
            t = 0;
            while (pow(abs((pow(User.getX(i,ptr[Day]) - Infected.getX(i, Infected.infected1ptr[Day]), 2) + pow(User.getY(k,ptr[Day]) - Infected.getY(i, Infected.infected1ptr[Day]), 2))), 0.5) <= R && k <= i + T2 / 30) {       //Ελέγχω αν θα ισχύσει η συνθήκη μετά από T2
                t = User.getTime(k, ptr[Day]) - User.getTime(i, ptr[Day]);        //Εκχωρώ στο t πόση ώρα ισχύει η συνθήκη
                u = t;                                                                  //Ώστε να μπορώ να ελέξγω την συνθήκη για τις τελευταίες Τ2 ώρες
                k++;
            }
            if (t >= T1) return true;
        }

 

        if (u != 0) {   //Ελέγχω τις τελευταίες Τ2 ώρες
            for (i = 2880 - T2 / 30; i <= 2880; i++) {
                if (pow(abs((pow(User.getX(i, ptr[Day]) - Infected.getX(i, Infected.infected1ptr[Day]), 2) + pow(User.getY(i, ptr[Day]) - Infected.getY(i, Infected.infected1ptr[Day]), 2))), 0.5) <= R) {      //Ελέγχω αν ισχύει η συνθήκη τις τελευταίες Τ2 ώρες
                    u += 30;        //Όσο ισχύει η συνθήκη αυξάνω το u κατά 30(δευτερόλεπτα)
                }
                else {  //Αν σταματήσει να ισχύει η συνθήκη, ελέγχω αν ο χρήστης έμεινε για τουλάχιστον Τ1, αν όχι βγαίνω από το loop 
                    if (u >= T1) { return true; }
                    else { break; }
                }
            }
        }
        t = 0;
        for (i = 2880 - T2 / 30; i <= 2880 - 1; i++) {
            if (pow(abs((pow(User.getX(i, ptr[Day]) - Infected.getX(i, Infected.infected1ptr[Day]), 2) + pow(User.getY(i, ptr[Day]) - Infected.getY(i, Infected.infected1ptr[Day]), 2))), 0.5) <= R) {
                t += 30;        //Όσο ισχύει η συνθήκη αυξάνω το t κατά 30(δευτερόλεπτα)
            }
            else {
                if (t >= T1) { return true; }   //Αν ο χρήστης βρέθηκε εντός ακτίνας R από τον ασθενή για διάστημα τουλάχιστον Τ1 λεπτών της ώρας επιστρέφει true,
                else { t = 0; }                   //διαφορετικά μηδενίζω το t ωστέ να ξαναγίνει ο έλεγχος
            }
        }
        //Έλεγχος χρήστη με το δεύτερο infected
        u = 0;
        for (i = 0; i <= 2880 - T2 / 30; i++) {     //Ελέγχω αν ισχύει η συνθήκη για τις πρώτες 24-Τ2 ώρες
            k = i;
            t = 0;
            while (pow(abs((pow(User.getX(k, ptr[Day]) - Infected2.getX(i, Infected2.infected2ptr[Day]), 2) + pow(User.getY(k, ptr[Day]) - Infected2.getY(i, Infected2.infected2ptr[Day]), 2))), 0.5) <= R && k <= i + T2 / 30) {       //Ελέγχω αν θα ισχύσει η συνθήκη μετά από T2
                t = User.getTime(k, ptr[Day]) - User.getTime(i, ptr[Day]);        //Εκχωρώ στο t πόση ώρα ισχύει η συνθήκη
                u = t;                                                                  //Ώστε να μπορώ να ελέξγω την συνθήκη για τις τελευταίες Τ2 ώρες
                k++;
            }
            if (t >= T1) return true;
        }

 

        if (u != 0) {   //Ελέγχω τις τελευταίες Τ2 ώρες
            for (i = 2880 - T2 / 30; i <= 2880; i++) {
                if (pow(abs((pow(User.getX(i, ptr[Day]) - Infected2.getX(i, Infected2.infected2ptr[Day]), 2) + pow(User.getY(i, ptr[Day]) - Infected2.getY(i, Infected2.infected2ptr[Day]), 2))), 0.5) <= R) {      //Ελέγχω αν ισχύει η συνθήκη τις τελευταίες Τ2 ώρες
                    u += 30;        //Όσο ισχύει η συνθήκη αυξάνω το u κατά 30(δευτερόλεπτα)
                }
                else {  //Αν σταματήσει να ισχύει η συνθήκη, ελέγχω αν ο χρήστης έμεινε για τουλάχιστον Τ1, αν όχι βγαίνω από το loop 
                    if (u >= T1) { return true; }
                    else { break; }
                }
            }
        }
        t = 0;
        for (i = 2880 - T2 / 30; i <= 2880 - 1; i++) {
            if (pow(abs((pow(User.getX(i, ptr[Day]) - Infected2.getX(i, Infected2.infected2ptr[Day]), 2) + pow(User.getY(i, ptr[Day]) - Infected2.getY(i, Infected2.infected2ptr[Day]), 2))), 0.5) <= R) {
                t += 30;        //Όσο ισχύει η συνθήκη αυξάνω το t κατά 30(δευτερόλεπτα)
            }
            else {
                if (t >= T1) { return true; }   //Αν ο χρήστης βρέθηκε εντός ακτίνας R από τον ασθενή για διάστημα τουλάχιστον Τ1 λεπτών της ώρας επιστρέφει true,
                else { t = 0; }                   //διαφορετικά μηδενίζω το t ωστέ να ξαναγίνει ο έλεγχος
            }
        }
        if (pow(abs((pow(User.getX(i, ptr[Day]) - Infected.getX(i, Infected.infected1ptr[Day]), 2) + pow(User.getY(i, ptr[Day]) - Infected.getY(i, Infected.infected1ptr[Day]), 2))), 0.5) <= R || pow(abs((pow(User.getX(i, ptr[Day]) - Infected2.getX(i, Infected2.infected2ptr[Day]), 2) + pow(User.getY(i, ptr[Day]) - Infected2.getY(i, Infected2.infected2ptr[Day]), 2))), 0.5) <= R) cout << "Day ended!" << endl;
        //Ελέγχω αν ισχύει στο τέλος της ημέρας(i=2880), αν ισχύει ενημερώνω τον χρήστη ότι τελείωσε η ημέρα
        return false;
    }

//Συνάρτηση που εισάγει κόμβους σε σημεία της λίστας που λείπουν διότι χάθηκε το σήμα του GPS
    void REPAIR(int Day,LinkedList User,node<int> *ptr[]){//παίρνει ως ορίσματα την ημέρα στην οποία βρισκόμαστε, τον χρήστη που θέλουμε να επεξεργαστούμε και τον δείκτη που δείχνει στον πρώτο κόμβο της ημέρας
        for(int i=0;i<=2880;i++){//δημιουργούμε ένα βρόχο που τρέχει για μία μέρα δηλαδή για 2880*30=86400 δευτερόλεπτα που αντιστοιχούν σε μία μέρα
            if(User.getTime(i+Day,ptr[Day]) != i*30+Day*2881*30){//ελέγχω αν μέσα στους κόμβους που έχουμε ήδη προσθέσει αντιστοιχεί η σωστή ώρα (i*30+Day*2881*30)
                //αν δεν αντιστοιχεί η ώρα μέσα στον κόμβο στην σωστή ώρα που θα έπρεπε να είναι τότε μέσω της διαδικασίας Insert εισάγουμε ένα νέο κόμβο πριν τον κόμβο που μόλις ελέγξαμε με την ώρα που λείπει (i*30+Day*2881*30)
                User.Insert(i+Day+1,User.getX(i+Day-1,ptr[Day])+(User.getX(i+Day+1,ptr[Day])-User.getX(i+Day-1,ptr[Day]))/2,User.getY(i+Day-1,ptr[Day])+(User.getY(i+Day+1,ptr[Day])-User.getY(i+Day-1,ptr[Day]))/2,i*30+Day*2881*30,ptr[Day]);
                //όσον αφορά τις συντεταγμένες στις οποίες θα βρίσκεται ο χρήστης εκείνη τη στιγμή πέρνουμε ένα μέσο όρο των συντεταγμένων που βρισκόταν στον προηγούμενο και στον επόμενο κόμβο δηλαδή x1 = x0+(x2-x0)/2 και αντίστοιχα για το y αν θεωρήσουμε οτι x0 είναι ο προηγούμενος κόμβος, x1 αυτός που προσθέτουμε εμείς και x2 ο επόμενος
            }
        }
    }

//Συνάρτηση που πηγαίνει μερικές μέρες πίσω από την τωρινή μέρα και ελέγχει την τροχιά του χρήστη και την συνοψίζει ώστε να γίνει πιο εύκολα κατανοητή από τον διαχειριστή του προγράμματος
    void SUMMARIZE_TRAJECTORY(int Day,int DaysBefore,LinkedList User,node<int> *ptr[]){//παίρνει ως ορίσματα την ημέρα στην οποία βρισκόμαστε,πόσες ημέρες πίσω θέλουμε να ελέγξουμε, τον χρήστη που θέλουμε να επεξεργαστούμε και τον δείκτη που δείχνει στον πρώτο κόμβο της ημέρας
        DaysBefore = DaysBefore +1;//προσθέτουμε +1 στο DaysBefore γιατί για παράδειγμα αν ο χρήστης βάλει Days=5 και DaysBefore=3 θέλουμε να πάμε στην δεύτερη μέρα που όμως επειδή ξεκινάμε απο το 0 είναι η 1 δηλαδη Days-DaysBefore=5-(3+1)=1
        int R = 10;//Η ακτίνα η οποία εξετάζουμε
        int j=0;//μετρήτης που ορίζει το κέντρο του κύκλου του οποίου εξετάζουμε την ακτίνα
        int n=1;//μετρητής που ορίζει το σημείο που εξετάζουμε αν ανήκει μέσα στην ακτίνα ή όχι
        for(int i=0;i<=2880;i++){//δημιουργούμε ένα βρόχο που τρέχει για μία μέρα δηλαδή για 2880*30=86400 δευτερόλεπτα που αντιστοιχούν σε μία μέρα
            //ελέγχουμε την συνθήκη ((x-x0)^2+(y-y0))^1/2 <= R δηλαδή εξετάζουμε αν η απόσταση του σημείου από το κέντρο είναι μικτότερη ή ίση σε σχέση από την ακτίνα
            if( pow(abs((pow(User.getX(n,ptr[Day-DaysBefore]) - User.getX(j,ptr[Day-DaysBefore]),2) + pow(User.getY(n,ptr[Day-DaysBefore]) - User.getY(j,ptr[Day-DaysBefore]),2))),0.5) <= R){
                User.Delete(j+2,ptr[Day-DaysBefore]);//αν ισχύει η σχέση αυτή τότε διαγράφουμε τον κόμβο του σημείου αυτού αφού οι συντεταγμένες του είναι πολύ κοντά στο κέντρο
            }else{
                j=n;//αν δεν ισχύει η συνθήκη αυτή δεν διαγράφουμε το σημείο αυτό και μέσω της j=n το ορίζουμε ως το καινούριο κέντρο
                cout << "  (x,y) = (" << User.getX(n,ptr[Day-DaysBefore]) << ',' << User.getY(n,ptr[Day-DaysBefore]) << ") " << endl;//εμφανίζουμε στον χρήστη την σύνοψη των σημείων της τροχίας του συγκεκριμένου healthy1
                n++;//αυξάνουμε τον μετρητή n κατά 1 για να εξετάσουμε το επόμενο σημείο
            }
        }
    }
};

//Συνάρτηση που επιστρέφει το πλήθος των χρηστών που βρέθηκαν εντός μίας τετραγωνικής περιοχής για την ημέρα στην οποία βρισκόμαστε
int FIND_CROWDED_PLACES(int Day, int TimeIntervalStart, int TimeIntervalEnd, int SquareRegionofInterest[4], int Tmin, LinkedList<int> User1,LinkedList<int> User2, LinkedList<int> infected1, LinkedList<int> infected2) {//παίρνει ως ορίσματα την ημέρα στην οποία βρισκόμαστε,την αρχή του χρονικού διαστήματος,το τέλος του χρονικού διαστήματος,τα όρια της τετραγωνικής περιοχής,το ελάχιστο χρονικό διάστημα που έπρεπε να παραμείνουν σε αυτήν την περιοχή, τους χρήστες
    int x1 = SquareRegionofInterest[0];      //A(x1,y1)
    int y1 = SquareRegionofInterest[1];
    int x2 = SquareRegionofInterest[2];      //B(x2,y2)
    int y2 = SquareRegionofInterest[3];
    int count = 0;  //Αρχικοποιώ με 0 το πλήθος των χρηστών
    //Για να βρίσκεται ο χρήστης μέσα στο Square Region of Interest πρέπει η τετμημένη του να είναι ανάμεσα από τα x1,x2 καθώς και η τεταγμένη του ανάμεσα από τα y1,y2
    //Τα x1,x2,y1,y2 έχουν δοθεί από τον χρήστης της εφαρμογής
    //Ελέγχω αν ο πρώτος χρήστης ικανοποιεί τις συνθήκες
    for (int i = TimeIntervalStart / 30; i <= TimeIntervalEnd / 30; i++) {  //Ο μετρητής i ξεκινάει από την αρχή του TimeInterval και τελειώνει στο τέλος του TimeInterval
        int k = i;  //νέος μετρητής
        int t = 0;  //πόση ώρα έμεινε
        while (User1.getX(k, User1.healthy1ptr[Day]) >= x1 && User1.getX(k, User1.healthy1ptr[Day]) <= x2 && User1.getY(k, User1.healthy1ptr[Day]) >= y1 && User1.getY(k, User1.healthy1ptr[Day]) <= y2 && k <= i + Tmin / 30 && k <= TimeIntervalEnd / 30) {        //Μέσα στο Square Region of Interest && να μην ξεπερνάει ο νέος μετρητής το minimum duration &&  την τελική ώρα
            t = User1.getTime(k, User1.healthy1ptr[Day]) - User1.getTime(i, User1.healthy1ptr[Day]);    //Εκχωρώ στο t πόση ώρα έμεινε
            k++;
        }
        if (t >= Tmin) {
            count++;    //Αν ισχύει η συνθήκη αυξάνω το πλήθος κατά 1
            break;      //και βγαίνω από το loop ώστε να ελέγξω αν ισχύει για τους επόμενους
        }
    }
    //Ελέγχω αν ο δεύτερος χρήστης ικανοποιεί τις συνθήκες
    for (int i = TimeIntervalStart / 30; i <= TimeIntervalEnd / 30; i++) {  //Ο μετρητής i ξεκινάει από την αρχή του TimeInterval και τελειώνει στο τέλος του TimeInterval
        int k = i;  //νέος μετρητής
        int t = 0;  //πόση ώρα έμεινε
        while (User2.getX(k, User2.healthy2ptr[Day]) >= x1 && User2.getX(k, User2.healthy2ptr[Day]) <= x2 && User2.getY(k, User2.healthy2ptr[Day]) >= y1 && User1.getY(k, User2.healthy2ptr[Day]) <= y2 && k <= i + Tmin / 30 && k <= TimeIntervalEnd / 30) {        //Μέσα στο Square Region of Interest && να μην ξεπερνάει ο νέος μετρητής το minimum duration &&  την τελική ώρα
            t = User2.getTime(k, User2.healthy2ptr[Day]) - User2.getTime(i, User2.healthy2ptr[Day]);    //Εκχωρώ στο t πόση ώρα έμεινε
            k++;
        }
        if (t >= Tmin) {
            count++;    //Αν ισχύει η συνθήκη αυξάνω το πλήθος κατά 1
            break;      //και βγαίνω από το loop ώστε να ελέγξω αν ισχύει για τους επόμενους
        }
    }
    //Ελέγχω αν ο τρίτος χρήστης ικανοποιεί τις συνθήκες
    for (int i = TimeIntervalStart / 30; i <= TimeIntervalEnd / 30; i++) {  //Ο μετρητής i ξεκινάει από την αρχή του TimeInterval και τελειώνει στο τέλος του TimeInterval
        int k = i;  //νέος μετρητής
        int t = 0;  //πόση ώρα έμεινε
        while (infected1.getX(k, infected1.infected1ptr[Day]) >= x1 && infected1.getX(k, infected1.infected1ptr[Day]) <= x2 && infected1.getY(k, infected1.infected1ptr[Day]) >= y1 && infected1.getY(k, infected1.infected1ptr[Day]) <= y2 && k <= i + Tmin / 30 && k <= TimeIntervalEnd / 30) {        //Μέσα στο Square Region of Interest && να μην ξεπερνάει ο νέος μετρητής το minimum duration &&  την τελική ώρα
            t = infected1.getTime(k, infected1.infected1ptr[Day]) - infected1.getTime(i, infected1.infected1ptr[Day]);  //Εκχωρώ στο t πόση ώρα έμεινε
            k++;
        }
        if (t >= Tmin) {
            count++;    //Αν ισχύει η συνθήκη αυξάνω το πλήθος κατά 1
            break;      //και βγαίνω από το loop ώστε να ελέγξω αν ισχύει για τον επόμενο
        }
    }
    //Ελέγχω αν ο τέταρτος χρήστης ικανοποιεί τις συνθήκες
    for (int i = TimeIntervalStart / 30; i <= TimeIntervalEnd / 30; i++) {  //Ο μετρητής i ξεκινάει από την αρχή του TimeInterval και τελειώνει στο τέλος του TimeInterval
        int k = i;  //νέος μετρητής
        int t = 0;  //πόση ώρα έμεινε
        while (infected2.getX(k, infected2.infected2ptr[Day]) >= x1 && infected2.getX(k, infected2.infected2ptr[Day]) <= x2 && infected2.getY(k, infected2.infected2ptr[Day]) >= y1 && infected2.getY(k, infected2.infected2ptr[Day]) <= y2 && k <= i + Tmin / 30 && k <= TimeIntervalEnd / 30) {        //Μέσα στο Square Region of Interest && να μην ξεπερνάει ο νέος μετρητής το minimum duration &&  την τελική ώρα
            t = infected2.getTime(k, infected2.infected2ptr[Day]) - infected2.getTime(i, infected2.infected2ptr[Day]);  //Εκχωρώ στο t πόση ώρα έμεινε
            k++;
        }
        if (t >= Tmin) {
            count++;    //Αν ισχύει η συνθήκη αυξάνω το πλήθος κατά 1
            break;      //και βγαίνω από το loop
        }
    }
    return count;
}

int Coordinates(int c) {    //Συνάρτηση που επιστρέφει τις τετμημένες και τεταγμένες των σημειών Α, Β για το Square Region of Interest της FIND_CROWDED_PLACES
    int final;
        switch (c)
        {
        case 0:
            while (true) {      //Έλεγχος εγκυρότητας
                cout << "Type coordinate x of A (0-100)" << endl;
                cin >> final;
                while (cin.fail()) {       //Ελέγχω αν ο χρήστης δώσει int, αλλιώς ξαναζητάω την τιμή
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Wrong input. Try again!" << endl;
                    cout << "Type coordinate x of A (0-100)" << endl;
                    cin >> final;
                }
                if (final >= 0 && final <= 100) return final;
                else cout << "Wrong input. Try again!" << endl;
            }
        case 1:

 

            while (true) {      //Έλεγχος εγκυρότητας
                cout << "Type coordinate y of A (0-100)" << endl;
                cin >> final;
                while (cin.fail()) {       //Ελέγχω αν ο χρήστης δώσει int, αλλιώς ξαναζητάω την τιμή
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Wrong input. Try again!" << endl;
                    cout << "Type coordinate y of A (0-100)" << endl;
                    cin >> final;
                }
                if (final >= 0 && final <= 100) return final;
                else cout << "Wrong input. Try again!" << endl;
            }
        case 2:

 

            while (true) {      //Έλεγχος εγκυρότητας
                cout << "Type coordinate x of B (0-100)" << endl;
                cin >> final;
                while (cin.fail()) {       //Ελέγχω αν ο χρήστης δώσει int, αλλιώς ξαναζητάω την τιμή
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Wrong input. Try again!" << endl;
                    cout << "Type coordinate x of B (0-100)" << endl;
                    cin >> final;
                }
                if (final >= 0 && final <= 100) return final;
                else cout << "Wrong input. Try again!" << endl;
            }
        case 3:

 

            while (true) {      //Έλεγχος εγκυρότητας
                cout << "Type coordinate y of B (0-100)" << endl;
                cin >> final;
                while (cin.fail()) {       //Ελέγχω αν ο χρήστης δώσει int, αλλιώς ξαναζητάω την τιμή
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Wrong input. Try again!" << endl;
                    cout << "Type coordinate y of B (0-100)" << endl;
                    cin >> final;
                }
                if (final >= 0 && final <= 100) return final;
                else cout << "Wrong input. Try again!" << endl;
            }
        }
    }

int Start() {        //Συνάρτηση που επιστρέφει το TimeIntervalStart(για την FIND_CROWDED_PLACES)
    int start;
    while (true) {      //Έλεγχος εγκυρότητας
        cout << "Type Interval's start (0-23)" << endl;
        cin >> start;
        while (cin.fail()) {       //Ελέγχω αν ο χρήστης δώσει int, αλλιώς ξαναζητάω την τιμή
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong input. Try again!" << endl;
            cout << "Type Interval's start (0-23)" << endl;
            cin >> start;
        }
        if (start >= 0 && start <= 23) return start;
        else cout << "Wrong input. Try again!" << endl;
    }
}

int End(int start) {    //Συνάρτηση που επιστρέφει το TimeIntervalEnd(για την FIND_CROWDED_PLACES)
    int end;
    while (true) {      //Έλεγχος εγκυρότητας
        cout << "Type Interval's end (" << start + 1 << "-24)" << endl;
        cin >> end;
        while (cin.fail()) {       //Ελέγχω αν ο χρήστης δώσει int, αλλιώς ξαναζητάω την τιμή
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong input. Try again!" << endl;
            cout << "Type Interval's end (" << start + 1 << "-24)" << endl;
            cin >> end;
        }
        if (end > start && end <= 24)return end;
        else cout << "Wrong input. Try again!" << endl;
    }
}

int Tmin(int start, int end) {  //Συνάρτηση που επιστρέφει το MinimumStayDuration(για την FIND_CROWDED_PLACES)
    int minimum;
    while (true) {      //Έλεγχος εγκυρότητας
        cout << "Type the Minumum Stay Duration in the Square Region of Interest (1-" << (end - start) * 60 << " minutes)" << endl;
        cin >> minimum;
        while (cin.fail()) {       //Ελέγχω αν ο χρήστης δώσει int, αλλιώς ξαναζητάω την τιμή
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong input. Try again!" << endl;
            cout << "Type the Minumum Stay Duration in the Square Region of Interest (1-" << (end - start) * 60 << " minutes)" << endl;
            cin >> minimum;
        }
        if (minimum >= 1 && minimum <= (end - start) * 60) return minimum;
        else cout << "Wrong input. Try again!" << endl;
    }
}

//Συνάρτηση που αλλάζει τις συντεταγμένες του χρήστη σύμφωνα με το RandomWaypointModel
void Movement(int& x, int& y, bool& possibilityOfStaying) {//παίρνει τρία ορίσματα την τιμή της x,της y και την πιθανότητα που έχει να μείνει σε κάποιο μέρος(η οποία είναι true αν έχει σταματήσει προηγουμένως σε κάποιο σημείο)
//βάζουμε το &x διότι έτσι πάει στη θέση μνήμης και αλλάζει την x από εκεί και η αλλαγή της είναι ορατή σε όλο το πρόγραμμα αλλιώς αν δεν το βάζαμε θα ήταν μόνο μέσα στη συνάρτηση
    int immobile;//μεταβλητή που κρατάει την πιθανότητα που έχει ο χρήστης να μείνει ακίνητος (να μην αλλάξουν οι συντεταγμένες)
    if (possibilityOfStaying == false) {//αν η πιθανοτητα να μείνει κάπου είναι false
        immobile = rand() % 5; //τότε βάζουμε μία πιθανότητα 1/5 δηλαδή 20% πιθανότητα να μείνει στο ίδιο σημείο
    }
    else {//αλλιώς αν είναι true
        immobile = rand() % 10; // του βάζουμε μία 9/10 πιθανότητα
        if (immobile != 9) {//δηλαδή άμα επιλεχθούν αριθμοί οι οποίοι είναι διαφορετικοί του 9 τότε immobile=0
            immobile = 0;//άρα είναι 9/10 δηλαδη 90% πιθανότητα να μείνει ακίνητος (το οποίο το προσθέσαμε για να προσεγγίσουμε όσο γίνεται την πραγματικότητα δηλαδή αν κάποιος μείνει ακίνητος συνήθως θα κάτσει για κάποση ώρα σε αυτό το σημείο)
        }

    }
    if (immobile != 0) {//αν το immobile δεν ειναι 0 δηλαδή ο χρήστης δεν είναι ακίνητος τότε κινείται
        possibilityOfStaying = false;//εφόσον θα κινηθεί ορίζουμε το possibilityofstaying=false
        int r = rand() % 4;//επιλέγουμε τυχαία μία απο της 4 περιπτώσεις να κινηθεί πάνω, κάτω, δεξιά ή αριστερά (εφόσον κινείται ευθύγραμμα) 
        int spaces = 3 + rand() % 4;//επιλέγουμε τυχαία πόσα βήματα θα κινηθεί επιλεγουμε να κάνει τυχαία απο 3 εως 6 βήματα
        switch (r)//βάζουμε switch για να δούμε σε ποια κατεύθυνση θα κινηθεί τελικά
        {
        case 0://κινείται δεξιά
            x += spaces;//δηλαδή προσθέτουμε στο x = x + spaces
            if (x >= 100) {//άμα ξεπεράσει το όριο του πλέγματος DxD τότε
                x -= spaces;//αφαιρούμε τα βήματα που προσθέσαμε
                Movement(x, y, possibilityOfStaying);//και ξαναεκτελούμε την Movement μέχρι να πάρει σωστή τιμή το x
            }
            break;//break ώστε να μην εκτελεστούν τα άλλα cases
        case 1://κινείται αριστερά
            x -= spaces;//δηλαδή αφαιρούμε στο x = x - spaces
            if (x <= 0) {//άμα ξεπεράσει το όριο του πλέγματος DxD τότε
                x += spaces;//προσθέτουμε τα βήματα που αφαιρέσαμε
                Movement(x, y, possibilityOfStaying);//και ξαναεκτελούμε την Movement μέχρι να πάρει σωστή τιμή το x
            }
            break;
        case 2://κινείται πάνω
            y += spaces;//δηλαδή προσθέτουμε στο y = y + spaces
            if (y >= 100) {//άμα ξεπεράσει το όριο του πλέγματος DxD τότε
                y -= spaces;//αφαιρούμε τα βήματα που προσθέσαμε
                Movement(x, y, possibilityOfStaying);//και ξαναεκτελούμε την Movement μέχρι να πάρει σωστή τιμή το y
            }
            break;
        case 3://κινείται κάτω
            y -= spaces;//δηλαδή αφαιρούμε στο y = y - spaces
            if (y <= 0) {//άμα ξεπεράσει το όριο του πλέγματος DxD τότε
                y += spaces;//προσθέτουμε τα βήματα που αφαιρέσαμε
                Movement(x, y, possibilityOfStaying);//και ξαναεκτελούμε την Movement μέχρι να πάρει σωστή τιμή το y
            }
            break;
        default:
            break;
        }
    }
    else {//αν δεν κινηθέι ο χρήστης τότε κάνουμε την possibilityOfStaying = true
        possibilityOfStaying = true;
    }
}

int main()
{
    //χρησιμοποιούμε την srand για να ορίσουμε την τυχαιότητα των αριθμών άμα βάλουμε ένα σταθερό αριθμό τότε κάθε φορά που θα προσπαθούμε να παράξουμε τυχαίους αριθμούς θα καταλήγουμε μετά από λίγο στους ίδιους
    srand(time(0));//για αυτό βάζουμε το time(0) όπου μετράει συνεχώς την ώρα και θα αλλάζει συνέχεια τις τιμές των αριθμών ώστε να είναι πραγματικά τυχαίοι
    LinkedList<int> healthy1;//δημιουργούμε τον 1o user ο οποίος θα είναι υγιής
    LinkedList<int> healthy2;//δημιουργούμε τον 2o user ο οποίος θα είναι υγιής
    LinkedList<int> infected1;//δημιουργούμε τον 1o user ο οποίος θα είναι μολυσμένος
    LinkedList<int> infected2;//δημιουργούμε τον 2o user ο οποίος θα είναι μολυσμένος
    int cont = 1;//αρχικοποιούμε μία ακέραια μεταβλητή cont με την τιμή 1 για να τρέχει ο βρόχος συνεχώς μέχρι να τον σταματήσει ο χρήστης κάνοντας το cont != 1
    int i;//αρχικοποιούμε τον μετρητή i ο οποίος αυξάνεται ανα 30 δευτερόλεπτα
    int j = 0;//αρχικοποιούμε τον μετρητή j ο οποίος αυξάνεται ανά 1 ανάλογα τι μέρα είναι (σημείωση: ξεκινάμε το μέτρημα των μερών από το 0)
    int currenttime;//μεταβλητή που θα περιέχει την ώρα κάθε χρονική στιγμή για να προσθέσουμε στους κόμβους
    int errorchance;//μεταβλητή που έχει την πιθανότητα να μην εισάγει τον κόμβο για μία συγκεκριμένη ώρα μέσα στη λίστα (χάθηκε το σήμα του GPS) και στη συνέχεια το πρόβλημα διορθώνεται μέσω της Repair
    string c;//string για να επιβεβαιωθούμε ότι ο χρήστης διάβασε της πληροφορίες που του μεταδώσαμε και θέλει να συνεχιστεί το πρόγραμμα
    //healthy1
    int y = rand() % 101;//παράγουμε από το τετράπλευρο πλέγμα DxD δύο τυχάιες συντεταγμένες για κάθε χρήστη ως την αρχική τους θέση. Μία για το x
    int x = rand() % 101;// και μία για το y
    //infected1
    int y1 = rand() % 101;// τη διαδικασία αυτη την κάνουμε για κάθε χρήστη ξεχωριστά
    int x1 = rand() % 101;
    //infected2
    int y2 = rand() % 101;
    int x2 = rand() % 101;
    //healthy2
    int y3 = rand() % 101;
    int x3 = rand() % 101;
    bool in = false;//άλλη μία μεταβλητή bool που βοηθάει στην εισχώρηση των διευθύσεων των πρώτων κόμβων κάθε ημέρας μέσα σε ένα πίνακα
    bool possibilityOfStaying = false;//μεταβλητή που δείχνει αν έχει αυξηθεί η πιθανότητα που έχει ο χρήστης να κάτσει σε ένα συγκεκριμένο σημείο
    while (cont == 1) {//ατέρμονος βρόχος μέχρι να τον σπάσει ο χρήστης
        i = 0;//αρχικόποιούμε τον μετρητή i = 0 για να δηλώσουμε την αρχή της ημέρας (0 δευτερόλεπτα)
        while (i <= 2880) {//βρόχος που τρέχει για κάθε μέρα 2880 φορές διότι βάζουμε το i παντού στους κόμβους i*30 δηλαδή θα ουσιαστικά προσομοιώνει από το 0 έως το 30*2880=86400 δευτερόλεπτα (που ορίζουν τα δευτερόλεπτα που υπάρχουν σε μία μέρα) και αυξάνεται ανα 30 δευτερόλεπτα
            currenttime = 30 * i + j*2881*30;//ορίζουμε την τωρινή ώρα μέσω του τύπου αυτού και το j*2880 αντιστοιχεί σε ποια μέρα βρισκόμαστε
            errorchance = rand()%6000;//ορίζουμε την πιθανότητα του να μην εισαχθεί ένας κόμβος που θα είναι 1/6000 που είναι περίπου να γίνει μία φορα στις δύο μέρες
            if(errorchance != 0){//το παρακάτω block εκτελείται μόνο αν το errorchance είναι διαφορετικό του 0 που είναι 1/6000 πιθανότητα να συμβεί(δηλαδή αν δεν γίνει το παρακάτω block δεν θα εισαχθεί ο κόμβος)
                if(i == 2881-j && in==true && j!=0){// εισάγει μέσα στον πίνακα που έχουμε δημιουργήσει για κάθε χρήστη τις διευθύνσεις των κόμβων στην αρχή κάθε μέρας για τις μέρες 2 και μετά
                    healthy1.healthy1ptr[j+1]=healthy1.last;//πηγαίνουμε στην αντίστοιχει θέση του πίνακα και εισάγουμε τη διεύθυνση του κόμβου μέσω του healthy1.last που την έχει αποθηκευμένη
                    infected1.infected1ptr[j+1] = infected1.last;//αντίστοιχα για όλους τους χρήστες
                    infected2.infected2ptr[j+1]= infected2.last;
                    healthy2.healthy2ptr[j+1]= healthy2.last;
                }else if(i==0 && j==1){ // εισάγει μέσα στον πίνακα που έχουμε δημιουργήσει για κάθε χρήστη τις διευθύνσεις των κόμβων στην αρχή κάθε μέρας για την ημέρα 1
                    healthy1.healthy1ptr[j]=healthy1.last;
                    infected1.infected1ptr[j] = infected1.last;
                    infected2.infected2ptr[j] = infected2.last;
                    healthy2.healthy2ptr[j] = healthy2.last;
                    in = true;//κάνουμε το in = true ώστε να μη μπορεί να ξαναεκτελεστεί αυτή η else if και να πηγαίνει στην απο πάνω που ελέγχει για τις υπόλοιπες μέρες
                }
                healthy1.add(x, y,currenttime);//εισάγουμε την κάθε χρονική στιγμή ανα 30 τις συντεταγμένες x,y του χρήστη και την ώρα της στιγμής εκείνης μέσα στους κόμβους της συνδεδεμένης λίστας
                healthy2.add(x3, y3,currenttime);
                infected1.add(x1, y1,currenttime);//αντίστοιχα κάνουμε και για τους υπόλοιπους χρήστες
                infected2.add(x2, y2,currenttime);
                Movement(x, y, possibilityOfStaying);//αφού έχουμε εισάγει στην λίστα τον κόμβο με τα δεδομένα ενός χρήστη μέσω της Movement αλλάζουμε την τοποθεσία του χρήστη μέσω του μοντέλου RandomWaypointmodel ώστε να τροποποιείται η τροχία του
                Movement(x1, y1, possibilityOfStaying);//αντίστοιχα για τους υπόλοιπους χρήστες
                Movement(x2, y2, possibilityOfStaying);
                Movement(x3, y3, possibilityOfStaying);
                if(i ==0 && in==false){ //σε περίπτωση που το i=0 και in =false βρισκόμαστε στην ημέρα 0 στον πρώτο κόμβο και εισάγουμε την διεύθυνσή του μέσα στον αντίστοιχο πίνακα που κρατάει τις διευθύνσεις της αρχής της ημέρας
                    healthy1.healthy1ptr[j]=healthy1.last;// το j θα είναι 0 σε αυτή την περίπτωση άρα θα είναι το πρώτο στοιχείο που θα εισάγουμε στον πίνακα
                    infected1.infected1ptr[j] = infected1.last;
                    infected2.infected2ptr[j]= infected2.last;
                    healthy2.healthy2ptr[j]= healthy2.last;
                    //αυτή η if είναι μόνο για τον πρώτο κόμβο και δε θα ξαναεκτελεστεί διότι η if του 2ου κόμβου θα κάνει την in=true
                }
            }
            i += 1;//αυξάνουμε τον μετρητή i κατά 1 για να πάμε στα επόμενα 30 δευτερόλεπτα
        }

        healthy1.REPAIR(j,healthy1,healthy1.healthy1ptr);//εκτελείται η Repair για τον κάθε χρήστη και παίρνει ως ορίσματα την ημέρα που θα είναι j τον αντίστοιχο healthy1 και τον πίνακα του κάθε healthy1 που επειδή τον έχουμε δημιουργήσει μέσα στην τάξη LinkedList τον εμφανίζουμε μέσω ενός αντικειμένου δηλαδή healthy1.healthy1ptr
        healthy2.REPAIR(j,healthy2,healthy2.healthy2ptr);
        infected1.REPAIR(j,infected1,infected1.infected1ptr);
        infected2.REPAIR(j,infected2,infected2.infected2ptr);

        if (healthy1.POSSIBLE_COVID_19_INFECTION(healthy1, j, infected1, infected2, healthy1.healthy1ptr)) cout << "User 1 may have been infected." << endl;
        if (healthy2.POSSIBLE_COVID_19_INFECTION(healthy2, j, infected1, infected2, healthy2.healthy2ptr)) cout << "User 2 may have been infected." << endl;
        
        cout << "In order to create a Square Region of Interest you need to type the coordinates of 2 points(A and B)." << endl;      //FIND_CROWDED_PLACES
        cout << "A is up left and B is down right." << endl;
        int Ax = Coordinates(0);    //x1
        int Ay = Coordinates(1);    //y1
        int Bx = Coordinates(2);    //x2
        int By = Coordinates(3);    //y2
        int arr[] = { Ax,Ay,Bx,By };//Εκχωρώ στον πίνακα τις τιμές που έδωσε ο χρήστης της εφαρμογής
        int start = Start();        //TimeIntervalStart
        int end = End(start);       //TimeIntervalEnd
        int minimumStayDuration = Tmin(start, end);//MinimumStayDuration
        cout << FIND_CROWDED_PLACES(j, start * 3600, end * 3600, arr, minimumStayDuration * 60, healthy1, healthy2, infected1, infected2) << " people were in the Square Region of Interest." << endl;

        j++;//φτάνουμε στο τέλος του βρόχου άρα αυξάνουμε το j κατα 1 για να δείξουμε ότι αλλάξαμε μέρα

        if(j>=7){//για να εκτελέσουμε την SummarizeTrajectory θέλουμε να έχουν περάσει κάποσες μέρες για αυτό της εκτελούμε αφού περάσει μία βδομάδα
            cout << endl << "Summary of 1st user's Trajectory:" << endl;
            healthy1.SUMMARIZE_TRAJECTORY(j,6,healthy1,healthy1.healthy1ptr);//εκτελούμε την SummarizeTrajectory με ορίσματα την ημέρα που βρισκόμαστε (j) και ως DaysBefore βάζουμε το 6 ώστε όταν περάσει μία βδομάδα να πηγαίνει κάθε μέρα από τότε και να συνοψίζει την τροχία του healthy1 7 μέρες πίσω
            cout << endl << "Press any key to confirm when you are done checking the user's summarized trajectory." << endl;
            cin >> c;
            cout << endl << "Summary of 2nd user's Trajectory:" << endl;
            healthy2.SUMMARIZE_TRAJECTORY(j,6,healthy2,healthy2.healthy2ptr);
            cout << endl << "Press any key to confirm when you are done checking the user's summarized trajectory." << endl;
            cin >> c;
            cout << endl << "Summary of 3rd user's Trajectory:" << endl;
            infected1.SUMMARIZE_TRAJECTORY(j,6,infected1,infected1.infected1ptr);
            cout << endl << "Press any key to confirm when you are done checking the user's summarized trajectory." << endl;
            cin >> c;
            cout << endl << "Summary of 4th user's Trajectory:" << endl;
            infected2.SUMMARIZE_TRAJECTORY(j,6,infected2,infected2.infected2ptr);
            cout << endl << "If you want to continue to the next day press 1, else press any key." << endl;
            cin >> cont;//αν βάλει στο cont την τιμή 1 τότε το πρόγραμμα θα συνεχίσει αλλίως το πρόγραμμα σταματάει
            if(cont!=1){
                cout << "Program exited successfully." << endl;
            }
        }
    }
        return 0;
}
//Η εργασία αυτή δημιουργήθηκε από ομάδα δύο ατόμων (ΠΑΝΑΓΙΩΤΗΣ ΜΟΥΡΛΑΣ Π19108, ΧΡΗΣΤΟΣ-ΣΕΡΑΦΕΙΜ ΝΙΚΗΤΑΚΗΣ Π19121)