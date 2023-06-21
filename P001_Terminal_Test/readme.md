# Terminal Test

> https://wokwi.com/projects/367647266624927745

```javascript
int count = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  count++;
  Serial.println(String(count) + ".- Prueba...");
  delay(1000);
}
```