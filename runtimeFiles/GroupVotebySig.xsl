<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- Significant characters question updating -->
<!-- Import the identity transformation. -->

 <!--
   <xsl:import href="Identity.xsl"/>

   <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>

  -->


 <!-- <xsl:variable name="sigChars" select="3"/> <xsl:variable name="sigChars" select="%1"/>-->
<xsl:variable name="sigChars" select="3"/>


<!--  <xsl:key name="data-by-htn" match="v" use="substring(@fans,1, 2)" /> -->

 <xsl:template match="ssn/p[@idx='6']">
 <xsl:call-template name="makeSignificant22" />
  </xsl:template>

    <xsl:key name="cdlist" match="v" use="fanst" />
    <xsl:key name="data-by-htn" match="v" use="@fanst" />
    <xsl:key name="k" match="v" use="@fanst"/>

<xsl:key name="students" match="v" use="@fanst"/>


<xsl:template name="makeSignificant22">
<makeSignificant22>

<fuck>

ssss
<xsl:for-each select="./v[generate-id(key('students', @fanst)[1])]">
ggg <xsl:value-of select="concat('count(', count(key('students', ./@fanst)), '), ',
@fanst,., ' : ')"/>
<xsl:copy-of select="."/>
<!--
<xsl:value-of select="count(key('students', ./@fanst))"/> , <xsl:value-of select="@fanst"/> <xsl:copy-of select="."/> ddd
-->
</xsl:for-each>
xxxxxxxxx

<xsl:for-each select="v[count(. | key('data-by-htn', @fanst)[1]) = 1]">
   <xsl:sort select="@fanst" />
    <xsl:value-of select="@fanst" />
  <hr />

<!-- Now loop on the items of this Category,
                  We get them from the Key we defined -->
      <xsl:for-each select="key('data-by-htn', @fanst)">
        <!-- Sort by the item Value -->
        <xsl:sort select="@fanst" />
        <xsl:value-of select="@fanst" />
        <br />
      </xsl:for-each>

</xsl:for-each>
</fuck>
<!--
 <xsl:value-of select="count(. | key('data-by-htn', substring(@fans,1, 2))[1])"/>
    <xsl:for-each select="v[count(. | key('data-by-htn',substring(@fans,1, 1))[1]) = 1]">
-->
WTF number q6 aaa

</makeSignificant22>
</xsl:template>

<xsl:template name="makeSignificant01">

 <makeSignificant01>
    <Original><xsl:copy-of select="." /></Original>

<newsh_t>
<xsl:element name="{name(.)}">
    <xsl:for-each select="./@*">
    <xsl:choose>
        <xsl:when test="name(.) = 'sig'">
            <xsl:attribute name="{name(.)}"><xsl:value-of select="$sigChars"/></xsl:attribute>
        </xsl:when>

                            <xsl:otherwise>
                            <xsl:attribute name="{name(.)}">
                                <xsl:value-of select="."/>
                            </xsl:attribute>
                            </xsl:otherwise>
    </xsl:choose>
    </xsl:for-each>


    <!-- for each element -->
    <xsl:for-each select="./*">

        <xsl:choose>
              <!-- <xsl:when test="@respLS">-->
              <xsl:when test="name(.) = 'respLs'">
                <xsl:element name="{name(.)}"> <!-- respLs -->
                       <xsl:for-each select="./@*">

                            <xsl:attribute name="{name(.)}">
                                <xsl:value-of select="."/>
                            </xsl:attribute>
                        </xsl:for-each>

                        <!-- elements -->
                        <xsl:for-each select="./*">

                        <xsl:choose>

                            <xsl:when test="name(.) = 'respR'">
                               <!-- <xsl:copy-of select="." /> -->
                                <xsl:element name="{name(.)}">
                                    <!-- add new attrib or update -->

                                    <xsl:for-each select="./@*">
                                        <!-- <xsl:attribute name="{name(.)}">
                                        <xsl:value-of select="."/> </xsl:attribute> -->


<xsl:choose>
<xsl:when test="name(.) = 'respLS'">
<xsl:attribute name="{name(.)}"><xsl:value-of select="."/> </xsl:attribute>
<xsl:attribute name="sig_respLS"><xsl:value-of select="substring(.,1, $sigChars)"/> </xsl:attribute>
</xsl:when>
                            <xsl:otherwise> <!-- leave attributes unchanged -->
<xsl:copy-of select="." />
<!--  or this.                           <xsl:attribute name="{name(.)}"><xsl:value-of select="."/> </xsl:attribute>
-->
                            </xsl:otherwise>
                        </xsl:choose>

                                    </xsl:for-each>

                               </xsl:element>

                            </xsl:when>


                            <!-- other elements ignore -->
                            <xsl:otherwise>
                               <xsl:copy-of select="." />
                            </xsl:otherwise>
                        </xsl:choose>

                        </xsl:for-each>

                    </xsl:element> <!-- /respLs -->
              </xsl:when>



              <xsl:when test="name(.) = 'v'">
   <original1/> <xsl:copy-of select="." /> <_original2/>

                    <xsl:element name="{name(.)}DUCK">
                    <xsl:for-each select="./@*">

<xsl:choose>
<xsl:when test="name(.) = 'sig_ans'">
    <!-- have only one attrib by said name -->
</xsl:when>
<xsl:when test="name(.) = 'ans'">
   <xsl:attribute name="sig_{name(.)}"><xsl:value-of select="substring(.,1, $sigChars)"/> </xsl:attribute>
</xsl:when>

<xsl:otherwise>
   <xsl:copy-of select="." />
</xsl:otherwise>
</xsl:choose>

                    </xsl:for-each>
                    </xsl:element>
              </xsl:when>

                 <!-- Ignore other emlements -->
                 <xsl:otherwise>
                    <xsl:copy-of select="." />
                 </xsl:otherwise>
         </xsl:choose>
    </xsl:for-each>
</xsl:element>
</newsh_t>
</makeSignificant01>

</xsl:template>

   <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
