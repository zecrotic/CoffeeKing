void displaySugarDigit(int digit)
{
  switch (digit) //Case number will be the displayed digit
  {
    case 0:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, HIGH);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, LOW);
      break;
    case 1:
      digitalWrite(a_sugar, LOW);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, LOW);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, LOW);
      digitalWrite(g_sugar, LOW);
      break;
    case 2:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, LOW);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, HIGH);
      digitalWrite(f_sugar, LOW);
      digitalWrite(g_sugar, HIGH);
      break;
    case 3:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, LOW);
      digitalWrite(g_sugar, HIGH);
      break;
    case 4:
      digitalWrite(a_sugar, LOW);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, LOW);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;
    case 5:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, LOW);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;
    case 6:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, LOW);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, HIGH);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;
    case 7:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, LOW);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, LOW);
      digitalWrite(g_sugar, LOW);
      break;
    case 8:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, HIGH);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;
    case 9:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;
    case 10:
      digitalWrite(a_sugar, LOW);
      digitalWrite(b_sugar, LOW);
      digitalWrite(c_sugar, LOW);
      digitalWrite(d_sugar, LOW);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, LOW);
      digitalWrite(g_sugar, LOW);
      break;



  }

}
