#Rectagle Class Demo
class Rectagle:
    def _init_(self,width,height):
        self.width = width
        self.height = height
    
    def getArea(self):
        return self.width * self.height
recObj1 = Rectagle(2, 3)
recObj2 = Rectagle()

print(recObj1.getArea())
print(recObj2.getArea())