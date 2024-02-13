
 

-- 1. Displaying specified columns with weekday and expanded TransType:
SELECT CustomerID, TransDate, DATENAME(WEEKDAY, TransDate) AS WeekDay,
      CASE WHEN TransType = 'C' THEN 'Credit' ELSE 'Debit' END AS TransType,
      Amount
FROM Trans;


--2. Displaying credit and debit amounts separately with formatting:
SELECT CustomerID, 
       FORMAT(TransDate, 'MM/dd/yyyy') AS TransDate,
       CASE WHEN TransType = 'C' THEN Amount ELSE 0.00 END AS CreditAmount,
       CASE WHEN TransType = 'D' THEN Amount ELSE 0.00 END AS DebitAmount
FROM Trans;

-- 3. Filtering by month and year:
SELECT CustomerID, 
       FORMAT(TransDate, 'MM/dd/yyyy') AS TransDate,
       CASE WHEN TransType = 'C' THEN Amount ELSE 0.00 END AS CreditAmount,
       CASE WHEN TransType = 'D' THEN Amount ELSE 0.00 END AS DebitAmount
FROM Trans
WHERE MONTH(TransDate) = 4 AND YEAR(TransDate) = 2005;

--4. Displaying transactions on the first day of each month:
SELECT CustomerID, 
       FORMAT(TransDate, 'MM/dd/yyyy') AS TransDate,
       CASE WHEN TransType = 'C' THEN Amount ELSE 0.00 END AS CreditAmount,
       CASE WHEN TransType = 'D' THEN Amount ELSE 0.00 END AS DebitAmount
FROM Trans
WHERE TransDate = DATEADD(MONTH, DATEDIFF(MONTH, 0, TransDate), 0);


-- 5.  Displaying transactions on the last day of each month:
SELECT CustomerID, 
       FORMAT(TransDate, 'MM/dd/yyyy') AS TransDate,
       CASE WHEN TransType = 'C' THEN Amount ELSE 0.00 END AS CreditAmount,
       CASE WHEN TransType = 'D' THEN Amount ELSE 0.00 END AS DebitAmount
FROM Trans
WHERE TransDate = EOMONTH(TransDate);

-- 6. Aggregating credit and debit amounts by customer and year:
SELECT CustomerID, YEAR(TransDate) AS Year,
       SUM(CASE WHEN TransType = 'C' THEN Amount ELSE 0.00 END) AS CreditTotalAmount,
       SUM(CASE WHEN TransType = 'D' THEN Amount ELSE 0.00 END) AS DebitTotalAmount
FROM Trans
GROUP BY CustomerID, YEAR(TransDate);
