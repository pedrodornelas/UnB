{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
module Complex where

import Epsilon
import Control.Concurrent (yield)
import GHC.Float (int2Double)

data Complex = Rect Double Double
             | Polar Double Double

isRect :: Complex -> Bool
isRect (Rect _ _) = True
isRect (Polar _ _) = False 

isPolar :: Complex -> Bool
isPolar (Rect _ _) = False 
isPolar (Polar _ _) = True 

toPolar :: Complex -> Complex
toPolar (Rect x y) = Polar a f where
  a = sqrt (x^2 + y^2)
  f = atan (y/x)*180 / pi
toPolar (Polar a f) = Polar a f

toRect :: Complex -> Complex
toRect (Polar a f) = Rect x y where
  x = a*cos f
  y = a*sin f
toRect (Rect x y) = Rect x y

-- As funções abaixo permitem que comparemos
-- membros do tipo Complex.
instance Eq Complex where
  (Rect x y) == (Rect x' y') = x ≈ x' && y ≈ y'
  p1@(Polar _ _) == p2@(Polar _ _) = toRect p1 == toRect p2
  c@(Rect _ _) == p@(Polar _ _) = c == toRect p
  p@(Polar _ _) == c@(Rect _ _) = c == toRect p


-- Defina as operações da typeclass Num
-- para o tipo Complex.
instance Num Complex where
  (+) (Rect x y) (Rect a b) = Rect (x+a) (y+b)
  (+) c1 c2 = toRect c1 + toRect c2

  (-) (Rect x y) (Rect a b) = Rect (x-a) (y-b)
  (-) c1 c2 = toRect c1 - toRect c2

  (*) (Polar x y) (Polar a b) = Polar (x*a) (y+b)
  (*) c1 c2 = toPolar c1 * toPolar c2

  abs (Rect x y) = Rect (sqrt (x^2+y^2)) 0
  abs c = abs (toRect c)

  signum (Polar x y) = Polar 1 y
  signum c = signum (toPolar c)

  fromInteger n = Rect (fromIntegral n) 0

  negate (Rect x y) = Rect x (-y)
  negate c = negate (toRect c)

-- Defina a função show para um parâmetro Complex.
-- Essa função converte um elemento para uma string.
instance Show Complex where
  show (Rect x y) = show x ++ showy y
  
  show (Polar a f) = show a ++ "#" ++ show f

showy :: Double -> String
showy y = if y>=0 then positivey y
                  else " - " ++ show (abs y) ++ "i"

positivey :: Double -> String
positivey y = if y==0 then ""
                      else " + " ++ show y ++ "i"