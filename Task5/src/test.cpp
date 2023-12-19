#include "../source.cpp"
#include <gtest/gtest.h>

TEST(Task1Test, ValidValues) { 
    EXPECT_EQ(Task1("testfiles/matrix1_rows.txt", "testfiles/vector1_rows.txt", 4, 8, 10), "-1563\n12589\n15693\n58071\n24369\n-93975\n94960\n-33994\n");
    EXPECT_EQ(Task1("testfiles/matrix2_rows.txt", "testfiles/vector2_rows.txt", 6, 12, 10), "6773\n-72360\n13012\n140503\n-52771\n39743\n-92879\n5611\n-54892\n-72630\n-39142\n18451\n");
    EXPECT_EQ(Task1("testfiles/matrix3_rows.txt", "testfiles/vector3_rows.txt", 8, 16, 10), "-64961\n-35260\n-65927\n-45464\n71402\n27182\n52001\n-42644\n32233\n-25011\n-45629\n1899\n50839\n24414\n39866\n5680\n");
    EXPECT_EQ(Task1("testfiles/matrix4_rows.txt", "testfiles/vector4_rows.txt", 5, 10, 12), "-82972\n-26027\n-77285\n-51035\n31654\n17182\n32475\n-67536\n25083\n-2495\n");
}

TEST(Task1Test, InvalidValues) { 
    EXPECT_EQ(Task1("testfiles/matrix1_rows.txt", "testfiles/vector1_rows.txt", 0, 8, 10), "Error");
    EXPECT_EQ(Task1("testfiles/matrix1_rows.txt", "testfiles/vector1_rows.txt", 4, -1, 10), "Error");
    EXPECT_EQ(Task1("testfiles/matrix1_rows.txt", "testfiles/vector1_rows.txt", 4, 8, -5), "Error");
    EXPECT_EQ(Task1("testfiles/matrix1_rows.txt", "testfiles/vector1_rows.txt", 4, 7, 10), "Number of rows is not a multiple of processing unit number");
    EXPECT_EQ(Task1("testfiles/matrix18_rows.txt", "testfiles/vector1_rows.txt", 4, 8, 10), "No file containing matrix or file is corrupted");    
    EXPECT_EQ(Task1("testfiles/matrix1_rows.txt", "testfiles/vector18_rows.txt", 4, 8, 10), "No file containing vector or file is corrupted");      
}

TEST(Task2Test, ValidValues) { 
    EXPECT_EQ(Task2("testfiles/matrix1_cols.txt", "testfiles/vector1_cols.txt", 4, 10, 8), "-27253\n-2058\n18427\n31128\n-46014\n-50474\n-35317\n-15450\n47557\n43437\n");
    EXPECT_EQ(Task2("testfiles/matrix2_cols.txt", "testfiles/vector2_cols.txt", 6, 10, 12), "42908\n35857\n-51635\n77082\n-78871\n2517\n-38343\n-16490\n114862\n75893\n");
    EXPECT_EQ(Task2("testfiles/matrix3_cols.txt", "testfiles/vector3_cols.txt", 8, 10, 16), "-63242\n38302\n-20408\n-91768\n-52017\n50582\n37849\n-5154\n-46900\n26758\n");
    EXPECT_EQ(Task2("testfiles/matrix4_cols.txt", "testfiles/vector4_cols.txt", 5, 12, 10), "-76833\n21294\n46584\n5952\n-26432\n48979\n-78660\n32163\n-84559\n-71903\n26695\n-67492\n");
}

TEST(Task2Test, InvalidValues) { 
    EXPECT_EQ(Task2("testfiles/matrix1_cols.txt", "testfiles/vector1_cols.txt", -2, 10, 8), "Error");
    EXPECT_EQ(Task2("testfiles/matrix1_cols.txt", "testfiles/vector1_cols.txt", 4, 0, 8), "Error");
    EXPECT_EQ(Task2("testfiles/matrix1_cols.txt", "testfiles/vector1_cols.txt", 4, 10, -9), "Error");
    EXPECT_EQ(Task2("testfiles/matrix1_cols.txt", "testfiles/vector1_cols.txt", 4, 10, 7), "Number of columns is not a multiple of processing unit number");
    EXPECT_EQ(Task2("testfiles/matrix18_cols.txt", "testfiles/vector1_cols.txt", 4, 10, 8), "No file containing matrix or file is corrupted");    
    EXPECT_EQ(Task2("testfiles/matrix1_cols.txt", "testfiles/vector18_cols.txt", 4, 10, 8), "No file containing vector or file is corrupted");      
}
  
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

