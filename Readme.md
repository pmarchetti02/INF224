# INF224 - Pierre MARCHETTI

Les codes Java (client) et C++ (serveur) ont été achevés.

Avec la télécommande, il est possible de demander une liste d'objets, d'en afficher un à partir de son nom, et de le lire (list, display [nom] et play [nom]). Le dossier Data contient trois fichiers de test, comprenant des images et des vidéos, pour tester le programme.

La documentation avec Doxygen n'a pas été réalisée en raison de contraintes temporelles.

Pour lancer le serveur, suivi du client, exécutez la commande make run dans les répertoires appropriés (cpp et swing).

## Questions C++
### Etape 4
*Comment appelle-t'on ce type de méthode et comment faut-il les déclarer ?*

Une classe abstraite est une classe qui ne peut pas être directement instanciée, mais qui sert de modèle pour d'autres classes qui en héritent.

Une méthode virtuelle pure est une méthode qui n'a pas de définition dans la classe de base. Elle est donc obligatoire à implémenter dans les classes filles. La méthode afficher doit être déclarée comme virtuelle pure dans la classe de base. Pour cela, on utilise le mot-clé virtual suivi de = 0 dans la déclaration de la méthode, comme ceci : `virtual void afficher() const = 0;`

### Etape 5
*Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ?*

Le polymorphisme est une caractéristique clé de la programmation orientée objet qui permet de traiter des objets de différents types de manière uniforme. Il permet à une méthode d'être appelée sur des objets de différentes classes. La méthode appelée est celle de la classe fille et non de la classe mère.

*Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ?*

Dans le cas du C++, il est nécessaire de déclarer la méthode comme virtuelle dans la classe de base. Ici on appelle `play()` de la classe `Multimédia`. 

*Quel est le type des éléments du tableau : le tableau doit-il contenir des objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.*

Le type des éléments du tableau doit être un pointeur vers les objets. Si les objets sont stockés directement dans le tableau, ils seront tronqués à la taille de la classe de base. En utilisant des pointeurs, on a accès aux méthodes spécifiques à la classe dérivée. En Java, les tableaux peuvent contenir des objets. En C++, où la gestion de la mémoire est manuelle, on doit utiliser des pointeurs.

### Etape 7 
*Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait pas de fuite mémoire quand on détruit les objets ?*

Pour prévenir les fuites de mémoire, il est nécessaire de modifier toutes les classes qui utilisent la mémoire dynamique, c'est-à-dire les classes qui créent des objets avec new. Par conséquent, il faut modifier toutes les classes qui dérivent de Multimedia (à savoir Photo, Video et Film) ainsi que la classe Group.

*La copie d'objet peut également poser problème quand ils ont des variables d'instance qui sont des pointeurs. Quel est le problème et quelles sont les solutions ?*

Lorsque des objets contenant des variables d'instance qui sont des pointeurs sont copiés, les pointeurs sont copiés, mais pas la mémoire vers laquelle ils pointent. Cela peut entraîner la création de plusieurs objets pointant vers la même mémoire, ce qui peut corrompre la mémoire. Pour éviter cela, le constructeur de copie et l'opérateur d'affectation doivent être modifiés pour allouer une nouvelle mémoire aux variables d'instance qui sont des pointeurs et copier les valeurs de l'objet d'origine vers la nouvelle mémoire. C'est ce qu'on appelle une copie profonde.

### Etape 8 
*Le groupe ne doit pas détruire les objets quand il est détruit car un objet peut appartenir à plusieurs groupes (on verra ce point à la question suivante). On rappelle aussi que la liste d'objets doit en fait être une liste de pointeurs d'objets. Pourquoi ? Comparer à Java.*

Dans le contexte de la classe `Group`, les objets peuvent appartenir à plusieurs groupes. Si l'on stocke directement les objets dans la liste de groupes, des copies des objets sont créées chaque fois qu'un objet est ajouté à un nouveau groupe. Cela peut poser problème si l'on modifie l'objet dans un groupe, car les autres groupes continueront à contenir l'ancienne version de l'objet. On utilise donc des pointeurs d'objets. Chaque groupe contient un pointeur vers un objet et non une copie de l'objet lui-même. En Java, les objets sont stockés dans le tas (heap) alors qu'ils sont stockés dans le tas ou la pile en C++.

### Etape 10
*Les méthodes précédentes permettent d'assurer la cohérence de la base de données car quand on crée un objet on l'ajoute à la table adéquate. Par contre, ce ne sera pas le cas si on crée un objet directement avec new (il n'appartiendra à aucune table). Comment peut-on l'interdire, afin que seule la classe servant à manipuler les objets puisse en créer de nouveaux ?*

Pour empêcher la création directe d'objets avec new, on peut rendre le constructeur de la classe privé et créer une méthode statique publique pour créer de nouveaux objets.


## Questions Java
### Etape 1
*Lancez votre programme, cliquez plusieurs fois sur les deux premiers bouton, retaillez la fenêtre. Que constate-t'on ?*

On ne peut pas voir le texte qui dépasse du JTextArea, car il n'y a pas de scroll bar. Il faut donc ajouter un JScrollPane au JTextArea.