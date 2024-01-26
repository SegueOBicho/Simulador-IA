#include<Fuzzy.h>
#define RESET asm ("jmp (0x0000)")

int contador = 0;

Fuzzy *fuzzy = new Fuzzy();

FuzzySet *Breserva = new FuzzySet(0, 0, 0, 5);
FuzzySet *Bextremamente_baixa = new FuzzySet(5, 10, 10, 20);
FuzzySet *Bbaixa = new FuzzySet(15, 30, 40, 45);
FuzzySet *Bmedia = new FuzzySet(35, 50, 50, 70);
FuzzySet *Balta = new FuzzySet(60, 75, 75, 101);

FuzzySet *Tbaixissima = new FuzzySet(0, 10, 10, 20);
FuzzySet *Tbaixa = new FuzzySet(10, 30, 30, 50);
FuzzySet *Taceitavel = new FuzzySet(40, 55, 55, 80);
FuzzySet *Talta = new FuzzySet(70, 90, 90, 100);

FuzzySet *Liga = new FuzzySet(0, (1/3)*100, (1/3)*100, (2/3)*100);
FuzzySet *NaoLiga = new FuzzySet((1/3)*100, (2/3)*100, (2/3)*100, (3/3)*100+1);

void imprime_colunas() {
  Serial.begin(9600);
  Serial.println("");
  Serial.print("index");
  Serial.print(",");
  Serial.print("Regra1_1");
  Serial.print(",");
  Serial.print("Regra1_2");
  Serial.print(",");
  Serial.print("Regra1_3");
  Serial.print(",");
  Serial.print("Regra1_4");
  Serial.print(",");
  Serial.print("Regra2_1");
  Serial.print(",");
  Serial.print("Regra2_2");
  Serial.print(",");
  Serial.print("Regra2_3");
  Serial.print(",");
  Serial.print("Regra2_4");
  Serial.print(",");
  Serial.print("Regra3_1");
  Serial.print(",");
  Serial.print("Regra3_2");
  Serial.print(",");
  Serial.print("Regra3_3");
  Serial.print(",");
  Serial.print("Regra3_4");
  Serial.print(",");
  Serial.print("Regra4_1");
  Serial.print(",");
  Serial.print("Regra4_2");
  Serial.print(",");
  Serial.print("Regra4_3");
  Serial.print(",");
  Serial.print("Regra4_4");
  Serial.print(",");
  Serial.print("Regra5_1");
  Serial.print(",");
  Serial.print("Regra5_2");
  Serial.print(",");
  Serial.print("Regra5_3");
  Serial.print(",");
  Serial.print("Regra5_4");
  Serial.print(",");
  Serial.print("Entrada1");
  Serial.print(",");
  Serial.print("Entrada2");
  Serial.print(",");
  Serial.print("PertinenciaLiga");
  Serial.print(",");
  Serial.println("PertinenciaNãoLiga");
  Serial.print(",");
  Serial.println("Saída");
  Serial.print(",");
  Serial.println("Estado de Saída");
}

void setup() {
  // put your setup code here, to run once:
  imprime_colunas();
  randomSeed(analogRead(0));

  FuzzyInput *Bateria = new FuzzyInput(1);
  Bateria->addFuzzySet(Breserva);
  Bateria->addFuzzySet(Bextremamente_baixa);
  Bateria->addFuzzySet(Bbaixa);
  Bateria->addFuzzySet(Bmedia);
  Bateria->addFuzzySet(Balta);

  fuzzy->addFuzzyInput(Bateria);

  FuzzyInput *Taxa = new FuzzyInput(2);
  Taxa->addFuzzySet(Tbaixissima);
  Taxa->addFuzzySet(Tbaixa);
  Taxa->addFuzzySet(Taceitavel);
  Taxa->addFuzzySet(Talta);

  fuzzy->addFuzzyInput(Taxa);

  FuzzyOutput *GPRS = new FuzzyOutput(1);
  GPRS->addFuzzySet(Liga);
  GPRS->addFuzzySet(NaoLiga);
  fuzzy->addFuzzyOutput(GPRS); 

  // Regras 1
FuzzyRuleAntecedent *regras1_1 = new FuzzyRuleAntecedent();
regras1_1->joinWithAND(Breserva, Talta);
FuzzyRuleConsequent *saida_regra1_1 = new FuzzyRuleConsequent();
saida_regra1_1->addOutput(NaoLiga);
FuzzyRule *regra1_1 = new FuzzyRule(1, regras1_1, saida_regra1_1);
fuzzy->addFuzzyRule(regra1_1);

FuzzyRuleAntecedent *regras1_2 = new FuzzyRuleAntecedent();
regras1_2->joinWithAND(Breserva, Taceitavel);
FuzzyRuleConsequent *saida_regra1_2 = new FuzzyRuleConsequent();
saida_regra1_2->addOutput(NaoLiga);
FuzzyRule *regra1_2 = new FuzzyRule(2, regras1_2, saida_regra1_2);
fuzzy->addFuzzyRule(regra1_2);

FuzzyRuleAntecedent *regras1_3 = new FuzzyRuleAntecedent();
regras1_3->joinWithAND(Breserva, Tbaixa);
FuzzyRuleConsequent *saida_regra1_3 = new FuzzyRuleConsequent();
saida_regra1_3->addOutput(NaoLiga);
FuzzyRule *regra1_3 = new FuzzyRule(3, regras1_3, saida_regra1_3);
fuzzy->addFuzzyRule(regra1_3);

FuzzyRuleAntecedent *regras1_4 = new FuzzyRuleAntecedent();
regras1_4->joinWithAND(Breserva, Tbaixissima);
FuzzyRuleConsequent *saida_regra1_4 = new FuzzyRuleConsequent();
saida_regra1_4->addOutput(NaoLiga);
FuzzyRule *regra1_4 = new FuzzyRule(4, regras1_4, saida_regra1_4);
fuzzy->addFuzzyRule(regra1_4);

// Regras 2
FuzzyRuleAntecedent *regras2_1 = new FuzzyRuleAntecedent();
regras2_1->joinWithAND(Bextremamente_baixa, Talta);
FuzzyRuleConsequent *saida_regra2_1 = new FuzzyRuleConsequent();
saida_regra2_1->addOutput(Liga);
FuzzyRule *regra2_1 = new FuzzyRule(5, regras2_1, saida_regra2_1);
fuzzy->addFuzzyRule(regra2_1);

FuzzyRuleAntecedent *regras2_2 = new FuzzyRuleAntecedent();
regras2_2->joinWithAND(Bextremamente_baixa, Taceitavel);
FuzzyRuleConsequent *saida_regra2_2 = new FuzzyRuleConsequent();
saida_regra2_2->addOutput(Liga);
FuzzyRule *regra2_2 = new FuzzyRule(6, regras2_2, saida_regra2_2);
fuzzy->addFuzzyRule(regra2_2);

FuzzyRuleAntecedent *regras2_3 = new FuzzyRuleAntecedent();
regras2_3->joinWithAND(Bextremamente_baixa, Tbaixa);
FuzzyRuleConsequent *saida_regra2_3 = new FuzzyRuleConsequent();
saida_regra2_3->addOutput(NaoLiga);
FuzzyRule *regra2_3 = new FuzzyRule(7, regras2_3, saida_regra2_3);
fuzzy->addFuzzyRule(regra2_3);

FuzzyRuleAntecedent *regras2_4 = new FuzzyRuleAntecedent();
regras2_4->joinWithAND(Bextremamente_baixa, Tbaixissima);
FuzzyRuleConsequent *saida_regra2_4 = new FuzzyRuleConsequent();
saida_regra2_4->addOutput(NaoLiga);
FuzzyRule *regra2_4 = new FuzzyRule(8, regras2_4, saida_regra2_4);
fuzzy->addFuzzyRule(regra2_4);

// Regras 3

FuzzyRuleAntecedent *regras3_1 = new FuzzyRuleAntecedent();
regras3_1->joinWithAND(Bbaixa, Talta);
FuzzyRuleConsequent *saida_regra3_1 = new FuzzyRuleConsequent();
saida_regra3_1->addOutput(Liga);
FuzzyRule *fuzzyRule3_1 = new FuzzyRule(9, regras3_1, saida_regra3_1);
fuzzy->addFuzzyRule(fuzzyRule3_1);

FuzzyRuleAntecedent *regras3_2 = new FuzzyRuleAntecedent();
regras3_2->joinWithAND(Bbaixa, Taceitavel);
FuzzyRuleConsequent *saida_regra3_2 = new FuzzyRuleConsequent();
saida_regra3_2->addOutput(Liga);
FuzzyRule *fuzzyRule3_2 = new FuzzyRule(10, regras3_2, saida_regra3_2);
fuzzy->addFuzzyRule(fuzzyRule3_2);

FuzzyRuleAntecedent *regras3_3 = new FuzzyRuleAntecedent();
regras3_3->joinWithAND(Bbaixa, Tbaixa);
FuzzyRuleConsequent *saida_regra3_3 = new FuzzyRuleConsequent();
saida_regra3_3->addOutput(NaoLiga);
FuzzyRule *fuzzyRule3_3 = new FuzzyRule(11, regras3_3, saida_regra3_3);
fuzzy->addFuzzyRule(fuzzyRule3_3);

FuzzyRuleAntecedent *regras3_4 = new FuzzyRuleAntecedent();
regras3_4->joinWithAND(Bbaixa, Tbaixissima);
FuzzyRuleConsequent *saida_regra3_4 = new FuzzyRuleConsequent();
saida_regra3_4->addOutput(NaoLiga);
FuzzyRule *fuzzyRule3_4 = new FuzzyRule(12, regras3_4, saida_regra3_4);
fuzzy->addFuzzyRule(fuzzyRule3_4);

// Regras 4

FuzzyRuleAntecedent *regras4_1 = new FuzzyRuleAntecedent();
regras4_1->joinWithAND(Bmedia, Talta);
FuzzyRuleConsequent *saida_regra4_1 = new FuzzyRuleConsequent();
saida_regra4_1->addOutput(Liga);
FuzzyRule *fuzzyRule4_1 = new FuzzyRule(13, regras4_1, saida_regra4_1);
fuzzy->addFuzzyRule(fuzzyRule4_1);

FuzzyRuleAntecedent *regras4_2 = new FuzzyRuleAntecedent();
regras4_2->joinWithAND(Bmedia, Taceitavel);
FuzzyRuleConsequent *saida_regra4_2 = new FuzzyRuleConsequent();
saida_regra4_2->addOutput(Liga);
FuzzyRule *fuzzyRule4_2 = new FuzzyRule(14, regras4_2, saida_regra4_2);
fuzzy->addFuzzyRule(fuzzyRule4_2);

FuzzyRuleAntecedent *regras4_3 = new FuzzyRuleAntecedent();
regras4_3->joinWithAND(Bmedia, Tbaixa);
FuzzyRuleConsequent *saida_regra4_3 = new FuzzyRuleConsequent();
saida_regra4_3->addOutput(Liga);
FuzzyRule *fuzzyRule4_3 = new FuzzyRule(15, regras4_3, saida_regra4_3);
fuzzy->addFuzzyRule(fuzzyRule4_3);

FuzzyRuleAntecedent *regras4_4 = new FuzzyRuleAntecedent();
regras4_4->joinWithAND(Bmedia, Tbaixissima);
FuzzyRuleConsequent *saida_regra4_4 = new FuzzyRuleConsequent();
saida_regra4_4->addOutput(NaoLiga);
FuzzyRule *fuzzyRule4_4 = new FuzzyRule(16, regras4_4, saida_regra4_4);
fuzzy->addFuzzyRule(fuzzyRule4_4);

// Regras 5

FuzzyRuleAntecedent *regras5_1_antecedente = new FuzzyRuleAntecedent();
regras5_1_antecedente->joinWithAND(Balta, Talta);
FuzzyRuleConsequent *regras5_1_consequente = new FuzzyRuleConsequent();
regras5_1_consequente->addOutput(Liga);
FuzzyRule *regra5_1 = new FuzzyRule(17, regras5_1_antecedente, regras5_1_consequente);
fuzzy->addFuzzyRule(regra5_1);

FuzzyRuleAntecedent *regras5_2_antecedente = new FuzzyRuleAntecedent();
regras5_2_antecedente->joinWithAND(Balta, Taceitavel);
FuzzyRuleConsequent *regras5_2_consequente = new FuzzyRuleConsequent();
regras5_2_consequente->addOutput(Liga);
FuzzyRule *regra5_2 = new FuzzyRule(18, regras5_2_antecedente, regras5_2_consequente);
fuzzy->addFuzzyRule(regra5_2);

FuzzyRuleAntecedent *regras5_3_antecedente = new FuzzyRuleAntecedent();
regras5_3_antecedente->joinWithAND(Balta, Tbaixa);
FuzzyRuleConsequent *regras5_3_consequente = new FuzzyRuleConsequent();
regras5_3_consequente->addOutput(Liga);
FuzzyRule *regra5_3 = new FuzzyRule(19, regras5_3_antecedente, regras5_3_consequente);
fuzzy->addFuzzyRule(regra5_3);

FuzzyRuleAntecedent *regras5_4_antecedente = new FuzzyRuleAntecedent();
regras5_4_antecedente->joinWithAND(Balta, Tbaixissima);
FuzzyRuleConsequent *regras5_4_consequente = new FuzzyRuleConsequent();
regras5_4_consequente->addOutput(NaoLiga);
FuzzyRule *regra5_4 = new FuzzyRule(20, regras5_4_antecedente, regras5_4_consequente);
fuzzy->addFuzzyRule(regra5_4);

}

void loop() {
  // put your main code here, to run repeatedly:

  int input1 = random(0, 100);
  int input2 = random(0, 100);
  int out_class = 0;

  fuzzy->setInput(1, input1);
  fuzzy->setInput(2, input2);

  fuzzy->fuzzify();

  float output1 = fuzzy->defuzzify(1);

  if (Liga->getPertinence() > NaoLiga->getPertinence()){
    out_class = 1;
  }
  else if (Liga->getPertinence() <= NaoLiga->getPertinence()){
    out_class = 0;
  }

  Serial.print(contador); //1_1
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(1)); //1_1
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(2)); //1_2
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(3)); //1_3
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(4)); //1_4
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(5)); //2_1
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(6)); //2_2
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(7)); //2_3
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(8)); //2_4
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(9)); //3_1
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(10)); //3_2
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(11)); //3_3
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(12)); //3_4
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(13)); //4_1
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(14)); //4_2
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(15)); //4_3
  Serial.print(","); 
  Serial.print(fuzzy->isFiredRule(16)); //4_4
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(17)); //5_1
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(18)); //5_2
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(19)); //5_3
  Serial.print(",");
  Serial.print(fuzzy->isFiredRule(20)); //5_4
  Serial.print(",");
  Serial.print(input1);
  Serial.print(",");
  Serial.print(input2);
  Serial.print(",");
  Serial.print(Liga->getPertinence());
  Serial.print(",");
  Serial.print(NaoLiga->getPertinence());
  Serial.print(",");
  Serial.print(output1);
  Serial.print(",");
  Serial.println(out_class);
  contador = contador + 1;
  delay(200);
}
