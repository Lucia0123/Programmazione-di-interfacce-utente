import 'package:hello_world/hello_world.dart';   // hello_world.dart in lib

// a volte può fare comodo gestire oggetti di classe Object (classe madre di tutto)
Type tipo(Object o){
  return o.runtimeType;   // oppure if (o is int) ecc.
}

void main(List<String> arguments) {
  print("Questo è un esempio di ${5+25} interpolazione");
  print('Hello world: ${calculate()}!');
  print("Hello " "world 👩🏻‍💻👋🏻");   // win + .
  
  int n = 42;
  double nDec = 3.14 ;
  String s = "Ciao";
  bool b = true;

  var v = 123;
  print("La variabile v è di tipo: ${v.runtimeType}.");

  // variabili di tipo final non possono essere cambiate di valore
  final f = 345;    // final dà type inference
  
  // un valore const a differenza di final è conosciuto dall'inizio dell'esecuzione
  const c = false;

  // dalla classe Object derivano tutti gli oggetti in Dart
  Object o1 = 123;
  Object o2 = "boh";
  Object o3 = -1.2;

  print("$o1 è di tipo ${tipo(o1)}\n$o2 è di tipo ${tipo(o2)}\n$o3 è di tipo ${tipo(o3)}");

  // Dart è sia type-safe che null-safe
  // Ad esempio una stringa può essere null solo se è nullable
  // s = null; darebbe errore
  print("s è lunga ${s.length} caratteri");
  String? stringaNullable = "Ciao";
  print("stringa_nullable è lunga ${stringaNullable.length} caratteri");
  stringaNullable = null;
  print("stringa_nullable è lunga ${stringaNullable?.length ?? 0} caratteri");
  // 01:25:07

  final fruit = /*<String, double>*/{
    "apple" : 2,
    "kiwi"  : 4,
    "pear"  : 7
  };
  print(fruit.containsKey("kiwi"));

  var x;
  print(x.runtimeType);
  x = "sono una stringa";
  print(x.runtimeType);
}
